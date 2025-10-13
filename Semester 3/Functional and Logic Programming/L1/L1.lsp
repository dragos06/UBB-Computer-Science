(defun find_elem (Elem List)
  (cond
   ((null List) t)
   ((/= Elem (car List)) (find_elem Elem (cdr List)))
   (t NIL)
  )
)

(defun set_diff (List1 List2)
  (cond
   ((null List1) ())
   ((null List2) List1)
   ((find_elem (car List1) List2) (cons (car List1) (set_diff (cdr List1) List2)))
   (t (set_diff (cdr List1) List2))
   )
)
(print "a")
(print (set_diff '(6 3 4 2 1 7) '(2 5 3)))
(print (set_diff '(1 4 2 3 5) '()))
(print (set_diff '() '(1 2 3)))
(print (set_diff '() '()))
(terpri)

(defun rev_list (List)
 (cond
   ((atom List) List)
   (t (append (rev_list (cdr List)) (list (rev_list (car List)))))
   )
)

(print "b")
(print (rev_list '(1 2 3 4 5)))
(print (rev_list '(1 (2) 3 (4 5))))
(print (rev_list '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))
(print (rev_list '()))
(terpri)

(defun list_length (List)
  (cond
   ((null List) 0)
   (t (+ 1 (list_length (cdr List))))
   )
)

(defun first_elem (List Flag)
  (cond
    ((null List) ())
    ((and (= Flag 0) (atom (car List)) (= (mod (list_length List) 2) 1)) (cons (car List) (first_elem (cdr List) 1)))
    ((and (= Flag 0) (atom (car List)) (= (mod (list_length List) 2) 0)) (first_elem (cdr List) 1))
    ((and (= Flag 0) (listp (car List)) (= (mod (list_length List) 2) 1)) (append (cons (car List) (first_elem (car List) 0)) (first_elem (cdr List) 1)))
    ((and (= Flag 0) (listp (car List)) (= (mod (list_length List) 2) 0)) (append (first_elem (car List) 0) (first_elem (cdr List) 1)))
    ((and (= Flag 1) (atom (car List))) (first_elem (cdr List) 1))
    ((and (= Flag 1) (listp (car List)) (append (first_elem (car List) 0) (first_elem (cdr List) 1))))
  )
)

(defun main (List)
  (first_elem List 0)
)
(print "c")
(print (main '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))
(print (main '(((1 2 3) 2 3) 2 (3 (4 5) (6 7)) 8 (9 10 11))))
(print (main '(1)))
(print (main '()))
(terpri)


(defun superficial_sum (List)
  (cond
   ((null List) 0)
   ((numberp (car List)) (+ (car List) (superficial_sum (cdr List))))
   (t (superficial_sum (cdr List)))
   )
)
(print "d")
(print (superficial_sum '(1 2 3)))
(print (superficial_sum '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))
(print (superficial_sum '(((1 2 3) 2 3) 2 (3 (4 5) (6 7)) 8 (9 10 11))))

