% successor(List, Carry, Result)
% (i, i, o), (i, i, i)
successor([], 0, []):- !.
successor([], 1, [1]):- !.
successor([H|T], C, [HR|R]):-
    H + C =\= 10,
    !,
    HR is H + C,
    NewC is 0,
    successor(T, NewC, R).
successor([_|T], _, [HR|R]):-
    HR is 0,
    NewC is 1,
    successor(T, NewC, R).
successor([], []):-!.
successor(List, R):- 
    reverse(List, R1),
    successor(R1, 1, R2),
	reverse(R2, R).


% reverse(List, Collector, Result)
% (i, i, o), (i, i, i)
reverse([], C, C).
reverse([H|T], C, R):-
    reverse(T, [H|C], R).
reverse(List, Result):- reverse(List, [], Result).

% checkList(List)
% (i)
checkList([]).
checkList([_|T]):-
    checkList(T).

% successorList(List, Result)
% (i, o), (i, i)
successorList([], []).
successorList([H|T], [Res|R]):-
    checkList(H),
    !,
    successor(H, Res),
    successorList(T, R).
successorList([H|T], [H|R]):-
    successorList(T, R).