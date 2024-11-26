% find_min(List, Min, Result)
% (i, i, o)
find_min([], Min, Min).
find_min([H|T], Min, Result):-
    H < Min,
    !,
    NewMin is H,
    find_min(T, NewMin, Result).
find_min([_|T], Min, Result):-
    find_min(T, Min, Result).
find_min([H|T], Result):-
    find_min(T, H, Result).

% remove_first(List, Element, Occurences, Result).
% (i, i, i, o)
remove_first([], _, _, []).
remove_first([H|T], X, Occ, Result):-
    H =:= X,
    Occ =:= 0,
    !,
    NewOcc is 1,
    remove_first(T, X, NewOcc, Result).
remove_first([H|T], X, Occ, [H|Result]):-
    remove_first(T, X, Occ, Result).
remove_first(List, X, Result):-
    remove_first(List, X, 0, Result).

% my_sort(List, Result).
% (i, o)
my_sort([], []):-!.
my_sort(List, [Min|Result]):-
    find_min(List, Min),
    remove_first(List, Min, NewList),
    my_sort(NewList, Result).

% my_sort([6,2,5,3,6,7,0,-1,3,4], Result).