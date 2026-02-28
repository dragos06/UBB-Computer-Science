import re
import sys

def expand_range(expr):
    chars = []
    parts = [p.strip() for p in expr.split(',')]
    for part in parts:
        if '-' in part and len(part) == 3:
            start, end = part[0], part[2]
            chars.extend([chr(c) for c in range(ord(start), ord(end) + 1)])
        else:
            chars.append(part)
    return chars


def parse_grammar(file_path):
    with open(file_path, 'r') as f:
        text = f.read()

    nonterminals = re.findall(r'N\s*=\s*{([^}]*)}', text)[0]
    alphabet = re.findall(r'SIG\s*=\s*{([^}]*)}', text)[0]
    start_symbol = re.findall(r'S\s*=\s*{([^}]*)}', text)[-1].strip()

    N = [x.strip() for x in nonterminals.split(',')]
    SIG = []
    for expr in [x.strip() for x in alphabet.split(',')]:
        SIG.extend(expand_range(expr))

    tokens = {}
    token_section = re.search(r'Tokens:\s*(.*?)(?:S\s*=|$)', text, re.S)
    if token_section:
        token_lines = token_section.group(1).splitlines()
        for line in token_lines:
            if '=' in line:
                name, value = line.split('=')
                tokens[name.strip()] = expand_range(value.strip())

    productions_text = re.findall(r'P:\s*(.*?)(?:Tokens:|S\s*=|$)', text, re.S)[0].strip()
    productions = []
    for line in productions_text.splitlines():
        line = line.strip()
        if not line or '→' not in line:
            continue
        left, right = line.split('→')
        left = left.strip()
        for alt in right.split('|'):
            alt = alt.strip()
            found_token = False
            for token, expansion in tokens.items():
                if token in alt:
                    found_token = True
                    for ch in expansion:
                        productions.append((left, alt.replace(token, ch)))
                    break
            if not found_token:
                productions.append((left, alt))

    return N, SIG, productions, start_symbol

def grammar_to_fa(N, SIG, productions, start_symbol):
    transitions = []
    final_states = set()
    final_state = 'F'

    for left, right in productions:
        right = right.replace(" ", "")

        if right == 'epsilon':
            final_states.add(left)
            continue

        if len(right) == 1 and right in SIG:
            transitions.append((left, right, final_state))
        elif len(right) >= 2 and right[0] in SIG and right[1:] in N:
            transitions.append((left, right[0], right[1:]))
        else:
            terminal = right[0]
            nonterminal = right[1:] if len(right) > 1 else final_state
            if terminal in SIG and (nonterminal in N or nonterminal == final_state):
                transitions.append((left, terminal, nonterminal))
            else:
                print(f"Skipped unsupported rule: {left} → {right}")

    states = set(N + [final_state])
    final_states.add(final_state)
    return states, SIG, start_symbol, final_states, transitions

def write_fa(file_path, states, alphabet, start_state, final_states, transitions):
    with open(file_path, 'w') as f:
        f.write(f"States: {{ {', '.join(sorted(states))} }}\n")
        f.write(f"Alphabet: {{ {', '.join(sorted(alphabet))} }}\n")
        f.write(f"Start state: {start_state}\n")
        f.write(f"Final states: {{ {', '.join(sorted(final_states))} }}\n")
        f.write("Transitions:\n")
        for (src, symbol, dst) in transitions:
            f.write(f"{src} --{symbol}--> {dst}\n")

def main():
    if len(sys.argv) != 3:
        print("Usage: python rg_to_fa.py <input_file> <output_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    N, SIG, productions, start_symbol = parse_grammar(input_file)
    states, alphabet, start_state, final_states, transitions = grammar_to_fa(N, SIG, productions, start_symbol)
    write_fa(output_file, states, alphabet, start_state, final_states, transitions)

    print(f"Conversion complete! FA written to {output_file}")


if __name__ == "__main__":
    main()
