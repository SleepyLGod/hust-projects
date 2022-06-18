(* task_2 *)

(* 编写函数evens: int list -> int list，要求对所有int list L, evens(L)执行的结果为L中所有偶数的子集，且该子集中数据的顺序与L中出现的顺序一致。*)
(* 
	例如：evens [1, 2, 3, 4] = [2, 4]
	     evens [1, 3, 5, 7] = [ ] 
*)

fun isDouble(x : int) : bool =
    if x mod 2 = 0 then true
    else false;

fun evens([] : int list) : int list = []
    | evens(x::L) = 
    if isDouble(x) then x::evens(L)
    else evens(L);


(* task_3 *)

(* 1. 编写高阶函数：toInt: int -> int list -> int. 对所有b>1和所有L: int list,如果L是一个b进制数的int list表示，函数toInt b L为其相应的整数值，toInt b的结果类型为：int list -> int.*)
    
(* 
	如： val base2ToInt = toInt 2;
        val 2 = base2ToInt [0,1];
*)

fun toInt (base : int) (digits : int list) : int = 
    case digits of 
      [] =>  0
    | d::digits' => d + base * toInt(base)(digits');


(* 2. 利用数学操作mod和div可以将任意十进制整数n表示成基于基数b的b进制数形式，如4210=1325  编写高阶函数  toBase: int -> int -> int list 实现该转换： toBase b n将十进制数n转换为b进制数的int list表述形式（b>1, n≥0）*)

fun toBase (base : int) (n : int) : int list =
    case n of
      0 => []
    | _ =>
        let val rem = n mod base
            val quo = n div base
        in rem::toBase(base)(quo)
    end; 


(* 3. 编写高阶函数 convert: int * int -> int list -> int list 对任意b1, b2 > 1和所有L: int list（L为一个b1进制数的int list表述形式），函数convert(b1, b2) L将b1进制数的int list表述L转换成b2进制数的int list表述，
	即满足 toInt b2 (convert(b1, b2) L) = toInt b1 L
*)

fun convert (base1 : int, base2 : int) (L : int list) : int list = 
    toBase(base2)(toInt(base1)(L));
