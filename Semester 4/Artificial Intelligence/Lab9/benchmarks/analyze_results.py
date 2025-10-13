import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import ttest_ind, wilcoxon
from itertools import combinations

# Load results
df = pd.read_csv("experiment_results.csv")

# Extract function, encoding, crossover
df["encoding"] = df["config"].apply(lambda x: x.split("_")[-2])
df["crossover"] = df["config"].apply(lambda x: x.split("_")[-1])
df["function"] = df["config"].apply(lambda x: "_".join(x.split("_")[:-2]))
df["config_short"] = df["encoding"] + "_" + df["crossover"]

# Configs to include
expected_configs = ["real_arithmetic", "real_blx", "binary_1point", "binary_2point"]

# Plot types and their kwargs
plot_kinds = {
    "box": {"func": sns.boxplot, "extra_kwargs": {}},
    "violin": {"func": sns.violinplot, "extra_kwargs": {}},
    "strip": {"func": sns.stripplot, "extra_kwargs": {"jitter": True}},
}

# For CSV output
summary_stats_rows = []
stat_tests_rows = []

# Generate plots and collect stats
for func in df["function"].unique():
    func_df = df[df["function"] == func].copy()
    func_df = func_df[func_df["config_short"].isin(expected_configs)]

    if func_df.empty:
        print(f"⚠️ No data found for {func}, skipping.")
        continue

    # --- Summary Stats ---
    for config in expected_configs:
        config_data = func_df[func_df["config_short"] == config]["fitness"]
        if not config_data.empty:
            summary_stats_rows.append({
                "function": func,
                "config": config,
                "best": config_data.min(),
                "mean": config_data.mean(),
                "std": config_data.std(),
                "median": config_data.median(),
                "n_runs": len(config_data)
            })

    # --- Pairwise Statistical Tests (T-Test and Wilcoxon) ---
    for (cfg1, cfg2) in combinations(expected_configs, 2):
        data1 = func_df[func_df["config_short"] == cfg1]["fitness"]
        data2 = func_df[func_df["config_short"] == cfg2]["fitness"]
        if len(data1) > 0 and len(data2) > 0:
            # Welch’s t-test (independent, unequal variances)
            t_stat, t_p = ttest_ind(data1, data2, equal_var=False)

            # Wilcoxon test only if lengths match and > 10
            if len(data1) == len(data2) and len(data1) > 10:
                try:
                    w_stat, w_p = wilcoxon(data1.values - data2.values)
                except:
                    w_stat, w_p = None, None
            else:
                w_stat, w_p = None, None

            stat_tests_rows.append({
                "function": func,
                "config1": cfg1,
                "config2": cfg2,
                "t_stat": t_stat,
                "t_p_value": t_p,
                "wilcoxon_stat": w_stat,
                "wilcoxon_p_value": w_p
            })

    # --- Plots ---
    for kind, config in plot_kinds.items():
        plt.figure(figsize=(8, 6))
        plot_func = config["func"]
        kwargs = config["extra_kwargs"]

        plot_func(
            x="config_short",
            y="fitness",
            data=func_df,
            hue="config_short",
            palette="Set2",
            legend=False,
            **kwargs
        )

        plt.title(f"{func.replace('_', ' ').title()} – {kind.title()} Plot")
        plt.xlabel("Configuration")
        plt.ylabel("Best Fitness")
        plt.xticks(rotation=20)
        plt.tight_layout()
        filename = f"{func}_{kind}_plot.png"
        plt.savefig(filename)
        print(f"✅ Saved {filename}")
        plt.close()

# Save CSVs
summary_df = pd.DataFrame(summary_stats_rows)
summary_df.to_csv("summary_stats.csv", index=False)
print("📊 Saved summary_stats.csv")

stat_tests_df = pd.DataFrame(stat_tests_rows)
stat_tests_df.to_csv("statistical_tests.csv", index=False)
print("📊 Saved statistical_tests.csv")
