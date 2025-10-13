(defun number_nodes(tree k)
  (cond
    ((null tree) (list 0))
    ((and (atom tree) (= k -1)) (list 1))
    ((atom tree) (list 0))
    (t (mapcan (lambda (x) (number_nodes x (- k 1))) tree))
  )
)

(defun main(tree k)
  (apply '+ (number_nodes tree k))
)

(print (main '(a (b (c)) (d) (e (f))) 1))
