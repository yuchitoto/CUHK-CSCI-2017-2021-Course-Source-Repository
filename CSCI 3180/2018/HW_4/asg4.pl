% CSCI3180 Principles of Programming Languages
%
% --- Declaration ---
%
% I declare that the assignment here submitted is original except for source
% material explicitly acknowledged. I also acknowledge that I am aware of
% University policy and regulations on honesty in academic work, and of the
% disciplinary guidelines and procedures applicable to breaches of such policy
% and regulations, as contained in the website
% http://www.cuhk.edu.hk/policy/academichonesty/
%
% Assignment 4
% Name : Wong Sin Yi
% Student ID : 1155110677
% Email Addr : 1155110677@link.cuhk.edu.hk


% Rules
sum(0,X,X).
sum(s(X),Y,s(Z)) :- sum(X,Y,Z).

% 1(a) natNum(X)
natNum(0).
natNum(s(X)) :- natNum(X).

% 1(b) lt(X,Y) 
lt(X,Y) :- sum(X,s(_),Y).

% 1(c) Give a query to find natural numbers less than 3.
% lt(X,s(s(s(0)))).

% 1(d) geq(X,Y) 
geq(X,Y) :- sum(Y,_,X).

% 1(e) max(X,Y,Z)
max(X,X,X).
max(X,Y,X) :- lt(Y,X).
max(X,Y,Y) :- lt(X,Y).

% 1(f) difference(X,Y,Z)
difference(X,Y,Z) :- sum(Z,Y,X).

% 1(g) mod(X,Y,Z) X mod Y is equal to Z
mod(X,Y,X) :- lt(X,Y).
mod(X,Y,Z) :- geq(X,Y),difference(X,Y,D),mod(D,Y,Z).


% 2(a)
%   bt(a, bt(b, nil, bt(d, nil, nil)),bt(c, bt(e, bt(f, nil, nil), bt(g, nil, nil)), nil)).

% 2(b)
isTree(nil).
isTree(bt(_, L, R)) :- isTree(L), isTree(R).

% 2(c)
isLeaf(X, bt(X, nil, nil)).
isLeaf(X,bt(_, L, _)) :- isLeaf(X,L).
isLeaf(X,bt(_, _, R)) :- isLeaf(X,R).

% 2(d)
numberOfLeaf(nil, 0).
numberOfLeaf(bt(_, nil, nil), s(0)).
numberOfLeaf(bt(_, L, nil), N) :- L = bt(_,_,_), numberOfLeaf(L, N).
numberOfLeaf(bt(_, nil, R), N) :- R = bt(_,_,_),numberOfLeaf(R, N).
numberOfLeaf(bt(_, L, R), N) :- R = bt(_,_,_),L = bt(_,_,_),numberOfLeaf(L, X), numberOfLeaf(R, Y), sum(X,Y,N).

% 2(e)
height(nil, 0).
height(bt(_, nil, nil), s(0)).
height(bt(_, L, nil), s(H)) :- L = bt(_,_,_),height(L, H).
height(bt(_, nil, R), s(H)) :- R = bt(_,_,_),height(R, H).
height(bt(_, L, R), s(H)) :- R = bt(_,_,_),L = bt(_,_,_),height(L, X), height(R, Y), max(X, Y, H).
