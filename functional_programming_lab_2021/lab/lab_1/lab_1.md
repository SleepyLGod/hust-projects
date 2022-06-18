## **lab 1**

------
+ **1. 下列模式能否与类型为int list的L匹配成功？如果匹配不成功，指出该模式的类型？（假设x为int类型）**

  + ```xml-dtd
    x::L			
    可以匹配非空list
    _::_			
    可以匹配非空list
    x::(y::L)		
    可以匹配非空且长度至少为2的list	
    (x::y)::L		
    不可匹配，该模式类型为int list list
    [x, y]			
    可以匹配有长度为2的int list
    ```

+ **2. 试写出与下列表述相对应的模式。如果没有模式与其对应，试说明原因。**

  + ```xml-dtd
    list of length 3                                 
    [x,y,z]
    lists of length 2 or 3                           
    无对应模式，list的长度是定值！
    Non-empty lists of pairs                         
    [(x,y)]
    Pairs with both components being non-empty lists 
    (x::L1,y::L2)
    ```

+ **3. 分析下述程序段（左边括号内为标注的行号）**

  ```xml-dtd
  val x : int = 3;
  val temp : int = x + 1;
  fun assemble (x : int, y : real) : int =
  let val g : real = let val x : int = 2
   		val m : real = 6.2 * (real x)
   		val x : int = 9001
   		val y : real = m * y
   	in y - m
   	end
  in x + (trunc g)
  end
  val z = assemble (x, 3.0)
  ```
  
  + ```xml-dtd
    第5行的x：绑定类型为int，值为2
    第6行的m：绑定类型为real，值为12.4
    第7行的x：绑定类型为int，值为9001
    assemble(x,3.0)计算的结果是27
    ```
  
+ **4. 指出下列代码的错误：**

  + ```xml-dtd
     (* pi: real *)
    val pi : real = 3.14159;
    
    (* fact: int -> int *)
    fun fact (0 : int) : int = 1
      | fact n = n * (fact (n - 1));
    
    (* f : int -> int *)
    fun f (3 : int) : int = 9
        f _ = 4;                                 前面应该加|
        
    (* circ : real -> real *)
    fun circ (r : real) : real = 2 * pi * r      应为 2.0 * pi * r
    
    (* semicirc : real -> real *)
    fun semicirc : real = pie * r                pie,r 无定义！
    
    (* area : real -> real *)
    fun area (r : int) : real = pi * r * r       (r:real)
    ```

+ **5. 在提示符下依次输入下列语句，观察并分析每次语句的执行结果。**

  ```xml-dtd
  3+ 4;
  3 + 2.0;
  it + 6;
  val it = “hello”;
  it + “ world”;
  it + 5;
  val a = 5;
  a = 6;
  a + 8; 
  val twice = (fn x => 2 * x);
  twice a;
  let x = 1 in x end;
  foo;
  [1, “foo”];
  ```

  + ```xml-dtd
    3 + 4;
    val it = 7 : int
    
    3 + 2.0;
    stdIn:7.1-7.8 Error: operator and operand don't agree [literal]
      operator domain: int * int
      operand:         int * real
      in expression:
        3 + 2.0   类型不一致
    
    it + 6;
    val it = 13 : int
    
    val it = “hello”;
    val it = "hello" : string
    
    it + “ world”;
    stdIn:1.5 Error: overloaded variable not defined at type
      symbol: +
      type: string   串连接应该用^
      
    it + 5;
    stdIn:1.5 Error: overloaded variable not defined at type
      symbol: +
      type: string  类型不匹配
    
    val a = 5;
    val a = 5 : int
    
    a = 6;
    val it = false : bool  判断是否相等
    
    a + 8; 
    val it = 13 : int
    
    val twice = (fn x => 2 * x);
    val twice = fn : int -> int
    
    twice a;
    val it = 10 : int
    
    let x = 1 in x end;   应该是val x = 1
    stdIn:9.1-9.8 Error: syntax error: deleting  LET ID EQUALOP
    stdIn:9.11 Error: syntax error found at IN
    
    foo; 无意义
    stdIn:1.2-1.5 Error: unbound variable or constructor: foo
    
    [1, “foo”]; list中元素类型应该一致
    stdIn:1.2-3.2 Error: operator and operand don't agree [literal]
      operator domain: int * int list
      operand:         int * string list
      in expression:
    1 :: "foo" :: nil
    ```

+ **6. 函数sum用于求解整数列表中所有整数的和，函数定义如下：**

  ```xml-dtd
  (* sum : int list -> int *)
  (* REQUIRES: true *)
  (* ENSURES: sum(L) evaluates to the sum of the integers in L. *)
  fun sum [] = 0
      | sum (x::L) = x + (sum L);
  ```

  **完成函数`mult`的编写，实现求解整数列表中所有整数的乘积：**

  ```xml-dtd
  (* mult : int list -> int *)
  (* REQUIRES: true *)
  (* ENSURES: mult(L) evaluates to the product of the integers in L. *)
  fun mult [ ] = 		(* FILL IN *)
      | mult (x ::L) = 	(* FILL IN *) 
  ```
  
  + ```xml-dtd
    fun mult [] = 1
    	| mult (x::L) = x * mult (L);
    ```
  
+ **7. 编写函数实现下列功能**

  ```xml-dtd
  （1）zip: string list * int list -> (string * int) list
   其功能是提取第一个string list中的第i个元素和第二个int list中的第i个元素组成结果list中的第i个二元组。如果两个list的长度不同，则结果的长度为两个参数list长度的最小值。
   
  （2）unzip: (string * int) list -> string list * int list
   其功能是执行zip函数的反向操作，将二元组list中的元素分解成两个list，第一个list中的元素为参数中二元组的第一个元素的list，第二个list中的元素为参数中二元组的第二个元素的list。
   对所有元素L1: string list和L2: int list，unzip( zip (L1, L2)) = (L1, L2)是否成立？如果成立，试证明之；否则说明原因。
  ```

  + ```xml-dtd
    fun zip (x::L1:string list, y::L2:int list) : (string * int) list = (x,y)::zip(L1, L2)
    	| zip ([]:string list, y::L2:int list) : (string * int) list = []
    	| zip (x::L1:string list, []:int list) : (string *int) list = []
    	| zip ([]:string list, []:int list) : (string * int) list = [];
    ```
  + ```xml-dtd
    fun unzip ([]:(string * int) list) : string list * int list = ([], [])
    	| unzip ((x, y)::L : (string * int) list) : string list * int list = 
    let
        val (a,b) = unzip (L)
    in 
        (x::a, y::b)
    end;
    val l3 = [("a",1), ("b",2)];
    val l4 = unzip (l3);
    
    在L1和L2长度不相等时不成立
    ```

+ **8.完成如下函数`Mult: int list list -> int`的编写,该函数调用`mult `实现`int list list`中所有整数乘积的求解。**

  ```xml-dtd
  (* mult : int list list -> int *)
  (* REQUIRES: true *)
  (* ENSURES: mult(R) evaluates to the product of all the integers in the lists of R. *)
   
  fun Mult [] =   (* FILL IN *)
      | Mult (r :: R) = 	(* FILL IN *)
  ```

  + ```xml-dtd
    fun mult[] = 1
    	| mult (x::L) = x * mult(L);
    
    fun Mult [] = 1
    	| Mult (x::L) = mult(x) * Mult(L);
    ```

+ **9. 函数`mult’`定义如下，试补充其函数说明，指出该函数的功能。**

  + ```xml-dtd
    (* mult’ : int list * int -> int *)
    (* REQUIRES: true *)
    (* ENSURES: mult’(L) evaluates to the product of the integers in L. *)
    
     fun mult'([ ], a) = a
     	| mult' (x :: L, a) = mult' (L, x * a);
    ```

+ **10.  编写递归函数square实现整数平方的计算，即square n = n * n。
      要求：程序中可调用函数double，但不能使用整数乘法（*）运算。**

  ```xml-dtd
  (* double : int -> int *)
  (* REQUIRES: n >= 0 *)
  (* ENSURES: double n evaluates to 2 * n.*)
  
  fun double (0 : int) : int = 0
      | double n = 2 + double (n - 1)
  ```

  + ```xml-dtd
    fun square (0 : int) : int = 0
    	| square (n) = square (n-1) + double (n) - 1;
    ```

