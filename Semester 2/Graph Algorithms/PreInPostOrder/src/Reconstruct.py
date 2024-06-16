class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def build_tree_pre_in(preorder, inorder):
    # Base case
    if not preorder or not inorder:
        return None

    # The first element in the preorder list is the root of the tree
    root_value = preorder[0]
    root = TreeNode(root_value)

    # Find the index of the root in the inorder list
    root_index_in_inorder = inorder.index(root_value)

    # Split the inorder list into left and right subtrees
    left_inorder = inorder[:root_index_in_inorder]
    right_inorder = inorder[root_index_in_inorder + 1:]

    # Split the preorder list into left and right subtrees
    left_preorder = preorder[1:1 + len(left_inorder)]
    right_preorder = preorder[1 + len(left_inorder):]

    # Recursively build the left and right subtrees
    root.left = build_tree_pre_in(left_preorder, left_inorder)
    root.right = build_tree_pre_in(right_preorder, right_inorder)

    return root


def build_tree_post_in(postorder, inorder):
    # Base case
    if not postorder or not inorder:
        return None

    # The last element in the postorder list is the root of the tree
    root_value = postorder[-1]
    root = TreeNode(root_value)

    # Find the index of the root in the inorder list
    root_index_in_inorder = inorder.index(root_value)

    # Split the inorder list into left and right subtrees
    left_inorder = inorder[:root_index_in_inorder]
    right_inorder = inorder[root_index_in_inorder + 1:]

    # Split the postorder list into left and right subtrees
    left_postorder = postorder[:len(left_inorder)]
    right_postorder = postorder[len(left_inorder):-1]

    # Recursively build the left and right subtrees
    root.left = build_tree_post_in(left_postorder, left_inorder)
    root.right = build_tree_post_in(right_postorder, right_inorder)

    return root


# Helper function to print the tree (in-order traversal)
def print_tree(root):
    if root:
        print_tree(root.left)
        print(root.value, end=' ')
        print_tree(root.right)


# Example usage:
preorder = [3, 9, 20, 15, 7]
inorder = [9, 3, 15, 20, 7]
postorder = [9, 15, 7, 20, 3]

print("Tree constructed from Pre-order and In-order:")
root_pre_in = build_tree_pre_in(preorder, inorder)
print_tree(root_pre_in)

print("\n\nTree constructed from Post-order and In-order:")
root_post_in = build_tree_post_in(postorder, inorder)
print_tree(root_post_in)
