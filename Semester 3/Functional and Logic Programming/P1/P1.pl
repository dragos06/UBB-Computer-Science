% even_list(List)
% (i)
even_list([]).
even_list([_,_|T]):-
    even_list(T).

% minim(Number1, Number2, Result)
% (i, i, o), (i, i, i)
minim(M1, M2, M1):-
    M1 =< M2.
minim(M1, M2, M2):-
    M1 > M2.

% minim_list(List, Collector, Result)
% (i, i, o), (i, i, i)
minim_list([], C, C).
minim_list([H|T], C, R):-
    minim(H, C, NewC),
    minim_list(T, NewC, R).

% minim_list_main(List, Result)
% (i, o), (i, i)
minim_list_main([H|T], R):-
    minim_list(T, H, R).

% delete_list(List, Value, Result)
% (i, i, o), (i, i, i)
delete_list([],_,[]).
delete_list([H|T],H,T):- !.
delete_list([H|T],X,[H|R]):-
    delete_list(T,X,R).

% main(List, Result)
% (i, o), (i, i)
main(List, Result):-
    minim_list_main(List, Min),
    delete_list(List, Min, Result).