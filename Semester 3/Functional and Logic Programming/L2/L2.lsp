(defun inorder_nodes (Tree)
  (cond
  ((null Tree) ())
  (t (append (inorder_nodes (cadr Tree)) (list(car Tree)) (inorder_nodes (caddr Tree))))
  )
)

(print (inorder_nodes '(A (B) (C (D) (E)))))
(print (inorder_nodes '()))
(print (inorder_nodes '(A (B (D) (E)) (C))))
(print (inorder_nodes '(A (B))))
