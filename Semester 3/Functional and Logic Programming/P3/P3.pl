% parentheses(N, Opened, Closed,Result)
% (i, o)

parentheses(N, Opened, Closed, []):-
    Opened + Closed =:= N.

parentheses(N, Opened, Closed, ['('|Result]):-
    Opened < N/2,
    NewOpened is Opened + 1,
    parentheses(N, NewOpened, Closed, Result).

parentheses(N, Opened, Closed, [')'|Result]):-
    Closed < Opened,
    NewClosed is Closed + 1,
    parentheses(N, Opened, NewClosed, Result).


parentheses(N, Result):-
    N mod 2 =:= 0,
    parentheses(N, 0, 0, Result).
