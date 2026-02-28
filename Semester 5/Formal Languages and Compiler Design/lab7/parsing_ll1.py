import sys

class Grammar:
    def __init__(self, filename):
        self.productions = {}
        self.ordered_productions = [] 
        self.non_terminals = set()
        self.terminals = set()
        self.start_symbol = None
        self.load_from_file(filename)

    def load_from_file(self, filename):
        with open(filename, 'r') as f:
            lines = f.readlines()
            
        reading_productions = False
        
        for line in lines:
            line = line.strip()
            if not line: continue
            
            if line.startswith("N ="):
                content = line.split("=")[1].strip()
                self.non_terminals = set(content.split())
                continue
            
            if line.startswith("E ="):
                content = line.split("=")[1].strip()
                self.terminals = set(content.split())
                continue

            if line.startswith("S ="):
                self.start_symbol = line.split("=")[1].strip()
                continue
            
            if line.startswith("P ="):
                reading_productions = True
                continue

            if reading_productions and "->" in line:
                lhs, rhs = line.split("->")
                lhs = lhs.strip()
                rhs_parts = [x.strip() for x in rhs.strip().split()]
                
                if lhs not in self.productions:
                    self.productions[lhs] = []
                
                self.productions[lhs].append(rhs_parts)
                self.ordered_productions.append((lhs, rhs_parts))

        for lhs in self.productions:
            for rhs in self.productions[lhs]:
                for symbol in rhs:
                    if symbol != 'epsilon' and symbol not in self.non_terminals:
                        self.terminals.add(symbol)

class LL1Gen:
    def __init__(self, grammar):
        self.grammar = grammar
        self.first_set = {n: set() for n in grammar.non_terminals}
        self.follow_set = {n: set() for n in grammar.non_terminals}
        self.parsing_table = {}
        self.has_conflicts = False
        
        print(">> Generating FIRST set...")
        self.generate_first()
        print(">> Generating FOLLOW set...")
        self.generate_follow()
        print(">> Building Parsing Table...")
        self.build_parsing_table()

    def compute_first_seq(self, sequence):
        first_result = set()
        if not sequence: return first_result
        
        symbol = sequence[0]
        
        if symbol == 'epsilon':
            first_result.add('epsilon')
        elif symbol in self.grammar.terminals:
            first_result.add(symbol)
        elif symbol in self.grammar.non_terminals:
            first_result.update(self.first_set[symbol])
            if 'epsilon' in self.first_set[symbol] and len(sequence) > 1:
                first_result.remove('epsilon')
                first_result.update(self.compute_first_seq(sequence[1:]))
        
        return first_result

    def generate_first(self):
        change = True
        while change:
            change = False
            for lhs in self.grammar.productions:
                for rhs in self.grammar.productions[lhs]:
                    rhs_first = self.compute_first_seq(rhs)
                    original_size = len(self.first_set[lhs])
                    self.first_set[lhs].update(rhs_first)
                    if len(self.first_set[lhs]) > original_size:
                        change = True

    def generate_follow(self):
        start_node = self.grammar.start_symbol
        if start_node in self.follow_set:
            self.follow_set[start_node].add('$') 

        change = True
        while change:
            change = False
            for lhs in self.grammar.productions:
                for rhs in self.grammar.productions[lhs]:
                    for i, symbol in enumerate(rhs):
                        if symbol in self.grammar.non_terminals:
                            beta = rhs[i+1:]
                            beta_first = self.compute_first_seq(beta)
                            
                            original_size = len(self.follow_set[symbol])
                            self.follow_set[symbol].update(beta_first - {'epsilon'})
                            
                            if not beta or 'epsilon' in beta_first:
                                self.follow_set[symbol].update(self.follow_set[lhs])
                                
                            if len(self.follow_set[symbol]) > original_size:
                                change = True

    def build_parsing_table(self):
        for prod_idx, (lhs, rhs) in enumerate(self.grammar.ordered_productions):
            first_alpha = self.compute_first_seq(rhs)
            
            for terminal in first_alpha:
                if terminal != 'epsilon':
                    self.add_to_table(lhs, terminal, prod_idx + 1)
            
            if 'epsilon' in first_alpha:
                for terminal in self.follow_set[lhs]:
                    self.add_to_table(lhs, terminal, prod_idx + 1)

    def add_to_table(self, non_term, term, prod_idx):
        if (non_term, term) in self.parsing_table:
            existing = self.parsing_table[(non_term, term)]
            if existing != prod_idx:
                print(f"  [CONFLICT DETECTED] Table[{non_term}, {term}]: Keeping Prod {existing}, Ignoring Prod {prod_idx}")
                self.has_conflicts = True
        else:
            self.parsing_table[(non_term, term)] = prod_idx

class Parser:
    def __init__(self, grammar, ll1_gen):
        self.grammar = grammar
        self.table = ll1_gen.parsing_table

    def parse(self, w):
        input_stack = w + ['$']
        working_stack = [self.grammar.start_symbol, '$']
        output_productions = []
        
        while True:
            top_input = input_stack[0]
            top_work = working_stack[0]

            if top_input == '$' and top_work == '$':
                return output_productions

            if top_work == top_input:
                input_stack.pop(0)
                working_stack.pop(0)
            elif (top_work, top_input) in self.table:
                prod_idx = self.table[(top_work, top_input)]
                output_productions.append(prod_idx)
                lhs, rhs = self.grammar.ordered_productions[prod_idx - 1]
                working_stack.pop(0) 
                if rhs != ['epsilon']:
                    for symbol in reversed(rhs):
                        working_stack.insert(0, symbol)
            else:
                print(f"ERROR: Syntax Error at token '{top_input}'. Expected from '{top_work}'")
                print(f"  Expected tokens: {sorted([t for (nt, t) in self.table if nt == top_work])}")
                return None

class Node:
    def __init__(self, symbol):
        self.symbol = symbol
        self.id = 0
        self.children = []
        self.parent = None

class TreeBuilder:
    def __init__(self, grammar):
        self.grammar = grammar
        self.prod_iterator = None

    def build_full_tree(self, production_indices):
        self.prod_iterator = iter(production_indices)
        return self._recursive_build(self.grammar.start_symbol)

    def _recursive_build(self, symbol):
        node = Node(symbol)
        
        if symbol in self.grammar.terminals or symbol == 'epsilon':
            return node
            
        try:
            prod_idx = next(self.prod_iterator)
        except StopIteration:
            return node 
            
        lhs, rhs = self.grammar.ordered_productions[prod_idx - 1]
        
        if rhs == ['epsilon']:
            child = Node('epsilon')
            child.parent = node
            node.children.append(child)
        else:
            for child_sym in rhs:
                child_node = self._recursive_build(child_sym)
                child_node.parent = node
                node.children.append(child_node)
        return node

    def print_table(self, root):
        queue = [root]
        idx = 1
        while queue:
            n = queue.pop(0)
            n.id = idx
            idx += 1
            for child in n.children:
                queue.append(child)
                
        print(f"\n{'Index':<10} {'Symbol':<20} {'Father':<10} {'Sibling':<10}")
        print("-" * 55)
        
        queue = [root]
        while queue:
            n = queue.pop(0)
            father_id = n.parent.id if n.parent else 0
            sibling_id = 0
            if n.parent:
                my_index = n.parent.children.index(n)
                if my_index + 1 < len(n.parent.children):
                    sibling_id = n.parent.children[my_index + 1].id
            
            print(f"{n.id:<10} {n.symbol:<20} {father_id:<10} {sibling_id:<10}")
            for child in n.children:
                queue.append(child)

def read_sequence_file(filename):
    with open(filename, 'r') as f:
        return f.read().split()

def read_pif_file(filename):
    sequence = []
    with open(filename, 'r') as f:
        for line in f:
            token = line.strip()
            if not token: 
                continue
            
            if token.startswith("ID("):
                sequence.append("ID")
            elif token.startswith("CONST("):
                sequence.append("CONST")
            else:
                sequence.append(token)
    return sequence

if __name__ == "__main__":
    print("\n" + "="*40)
    print(" REQUIREMENT 1: Seminar Grammar")
    print("="*40)
    
    g1 = Grammar("seminar_grammar.txt")
    gen1 = LL1Gen(g1)
    
    if gen1.has_conflicts:
        print("\n[RESULT] The Seminar Grammar is NOT LL(1). Conflicts found.")
    else:
        print("\n[RESULT] The Seminar Grammar IS LL(1).")
        
    seq_seminar = read_sequence_file("seq.txt")
    parser1 = Parser(g1, gen1)
    res1 = parser1.parse(seq_seminar)
    if res1:
        print("Parsed successfully! Productions:", res1)

    print("\n" + "="*40)
    print(" REQUIREMENT 2: My DSL Grammar")
    print("="*40)

    g2 = Grammar("my_grammar.txt")
    gen2 = LL1Gen(g2)
    
    if gen2.has_conflicts:
        print("\n[RESULT] My Grammar had conflicts.")
    else:
        print("\n[RESULT] My Grammar IS LL(1). No conflicts in parsing table.")

    seq_program1 = read_pif_file("pif.txt")
    
    parser2 = Parser(g2, gen2)
    res2 = parser2.parse(seq_program1)
    
    if res2:
        builder2 = TreeBuilder(g2)
        root2 = builder2.build_full_tree(res2)
        print("\n[Req 2.c] Father-Sibling Table:")
        builder2.print_table(root2)