
 (* CSCI3180 Principles of Programming Languages *)

 (* --- Declaration --- *)

 (* I declare that the assignment here submitted is original except for source *)
 (* material explicitly acknowledged. I also acknowledge that I am aware of *)
 (* University policy and regulations on honesty in academic work, and of the *)
 (* disciplinary guidelines and procedures applicable to breaches of such policy *)
 (* and regulations, as contained in the website *)
 (* http://www.cuhk.edu.hk/policy/academichonesty/ *)

 (* Assignment 4 *)
 (* Name : Wong Sin Yi *)
 (* Student ID : 1155110677 *)
 (* Email Addr : 1155110677@link.cuhk.edu.hk *)


datatype suit = Clubs | Diamonds | Hearts | Spades;
datatype rank = Jack | Queen | King | Ace | Num of int;
type card = suit * rank;

datatype color = Red | Black;
datatype move = Discard of card | Draw;

(* 3(1) abs *)
fun abs x = if x >= 0 then x else ~x; 

(* 3(2) cardColor *)
fun cardColor( Suit:suit ,_ ): color =
   case Suit of Clubs => Black
  | Diamonds => Red
  | Hearts => Red
  | Spades => Black;

(* 3(3) cardValue *)
fun cardValue(_, Rank:rank): int =
   case Rank of Ace => 11
  | Jack => 10
  | Queen => 10
  | King => 10
  | Num x => x;

(* 3(4) numOfCard *)
fun numOfCard nil = 0
  |  numOfCard(h::t) = 1 + numOfCard(t);

(* 3(5) removeCard(cardList, c) *)
fun removeCard(nil, c:card) = nil
  | removeCard(h :: t, c:card) = 
      if h = c then removeCard(t, c :card)  
      else h :: removeCard(t, c :card);
    
(* 3(6) sumCards(cardList, col) *)
fun sumCards(nil, col: color) = 0
  | sumCards(h :: t, col: color) =
      if cardColor(h) = col then cardValue(h) + sumCards(t, col)
      else 0  + sumCards(t, col);

(* 3(7) score *)
fun score(cardList: card list) = 
  abs(sumCards(cardList, Red) - sumCards(cardList, Black)) + (6 - numOfCard(cardList));

(* 3(8) runGame(cardList, moveList) *)
fun runGame(cardList: card list, moveList: move list) =
  let 
    fun run(handCard,[],playerCard) = score(playerCard)
      | run(handCard, h::t ,playerCard) = 
        case h of Discard x => run(handCard, t, removeCard(playerCard, x))
          | Draw => run(tl(handCard), t, hd(handCard)::playerCard)
  in
    run (cardList, moveList, [])
  end;
