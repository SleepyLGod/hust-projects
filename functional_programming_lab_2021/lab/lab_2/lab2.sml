(* test 4 *)
(* divisibleByThree  :  int -> bool *)
(* REQUIRES :  n >= 0 *)
(* ENSURES :  divisibleByThree n evaluates to true if n is a multiple of 3 and to false otherwise *)

fun divisibleByThree (0 : int) : bool = true
    | divisibleByThree(1 : int) : bool = false
    | divisibleByThree(2 : int) : bool = false
    | divisibleByThree(n : int) : bool =
    if n < 0 then divisibleByThree(abs(n))
    else divisibleByThree(n - 3);


(* test 5 *)
(* evenP : int -> bool *)
(* REQUIRES : n >= 0 *)
(* ENSURES : evenP n evaluates to true iff n is even. *)
fun evenP (0 : int) : bool = true
	| evenP 1 = false
	| evenP n = evenP(n - 2)

(* oddP : int -> bool *)
(* REQUIRES : n >= 0 *)
(* ENSURES : oddP n evaluates to true iff n is odd. *)
fun oddP (0 : int) : bool = false
	| oddP(1 : int) : bool = true
	| oddP n = oddP(n - 2);
val a=7;
val b=oddP(a);


(* test 6 *)
(* 实现两个int list数据的合并，且两个list中的元素在结果中交替出现，直至其中一个int list数据结束，而另一个int list数据中的剩余元素则直接附加至结果数据的尾部 *)
fun interleave(L1, []) = L1
    | interleave([], L2) = L2
    | interleave(x::L1, y::L2) = x::y::interleave(L1, L2);
val a = [1, 3, 5];
val b = [2, 4, 6, 7];
val c = interleave(a, b);


(* test 7 *)
(* 实现输出表参数的逆序输出 *)
fun reverse([]) = []
    | reverse(x::L) = reverse(L) @ [x]
val a = [1, 2, 3, 4, 5];
val b = reverse(a);

(* 实现输出表参数的逆序输出 *)
fun reverse' ([], y) = y
    |reverse' (x::L, y) = reverse'(L, x::y);

val a = [1, 2, 3, 4, 5];
val b = reverse'(l1);


(* test 8 *)

