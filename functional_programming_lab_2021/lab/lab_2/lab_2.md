## **lab_2**

+ **1.** **分析以下函数或表达式的类型**

  ```sml
  fun all (your, base) = 
  	case your of
  	0 => base
  	| _ => "are belong to us" :: all(your - 1, base)
  
  fun funny (f, []) = 0
  	| funny (f, x::xs) = f(x, funny(f, xs))
  	
  (fn x => (fn y => x)) "Hello, World!"
  ```

  > **`ans:`**
  >
  > ```sml
  > (* 类型：int* string list -> string list *)
  > (* 函数功能：在string list base前添加your个“are belong to us” *)
  > fun all (your,base)=
  > case your of
  > 0 => base
  > | _ => "are belong to us" :: all(your - 1, base);
  > ```
  > ```sml
  > (* 类型：('a * int -> int) * 'a list -> int *)
  > fun funny (f, []) = 0
  > | funny (f, x::xs) = f(x, funny(f, xs))
  > ```
  > ```sml
  > (* 'a -> 'b -> 'a *)
  > (* Hello,World是输入 *)
  > (fn x => (fn y => x)) "Hello, World!"
  
+ **2. 用归纳法证明`ins`函数和`isort`函数的正确性**

  ```sml
  (* 对任一整数x和有序整数序列L，函数ins(x, L) 计算结果为x和L中所有元素构成的一个有序序列 *)
  fun ins (x, []) = [x]
      | ins (x, y::L) = case compare(x, y) of
  		    GREATER => y::ins(x, L)
  		    | _ => x::y::L
  ```

  > **证明：**
  >
  > `ins(x, L)`。当`L`是空表时，结果为`[x]`，是一个有序序列。
  >
  > 假设对于长度`< k`的有序表`L`来说，`ins(x,L)`的结果均为`x`和`L`中所有元素构成的有序序列。
  >
  > 那么对于长度为`k`的有序表`L`来说：
  >
  > `ins(x,L)` 时会将`L`的首元素`y`取出，剩余部分为`Y`，即`L=y::Y`。
  >
  > 将`y`与`x`进行比较，
  >
  > 1. 如果x>y。则进行操作y::ins（x,Y）。因为Y的长度为k-1，而由假设可知，ins(x,Y)会得到一个有序表。然后将y加入这个有序表的首部。因为表L本身就是有序的，所以它的首元素y是整个表中最小的元素，如果x大于y的话，那么在加入x的排好序的列表中，y还应该是首元素。所以可得，当x>y时所得结果正确。
  >
  > 2. 如果x<=y。则直接将x放入L的首元素。因为y本身就是L中最小的元素，如果x仍小于y，那么只有将它放到首部才能构成有序序列。由此可知当x<=y所得结果正确。
  >
  > 综上可知，该函数能够达到要求。
  
  ```sml
  (* REQUIRES true *)
  (* ENSURES isort(L) = a sorted perm of L *)
  (* 对所有整数序列L，isort L计算得到L中所有元素的一个有序排列 *)
  fun isort [ ] = [ ]
     |   isort (x::L) = ins (x, isort L)
  ```

  > 证明：
  >
  > 对于空表来说，所得结果仍为空表。正确
  >
  > 假设对于所有长度<k的列表来说，所得结果均为一个递增的有序序列。
  >
  > 那么对于长度为k的列表L来说：
  >
  > 假设L=y::Y.
  >
  > 进行`isort（L）`=` ins( y , isort( Y ) )`
  >
  > 由于`Y`长度为`k - 1`，根据假设可知，`isort(Y)`的结果是一个有序序列，不妨将其设为Z。
  >
  > 然后进行`ins(x, Z)`。已经证毕，`ins()`的计算结果为`x`和`Z`中所有元素构成的一个有序序列。
  >
  > 所以可知，`isort`能够将列表元素进行排序。
  
+ **3. 分析下面菲波拉契函数的执行性能**

  ```sml
  fun fib n = if n<=2 then 1 else fib(n-1) + fib(n-2);
  ```
  
  > fib(n)的复杂度为`O(2^n)`
  
  ```sml
  fun fibber (0: int) : int * int = (1, 1)
    | fibber (n: int) : int * int =
        let val (x: int, y: int) = fibber (n-1)
        in (y, x + y)
        end
  ```

  >  fibber的复杂度为`O(n)`

+ **4.  定义函数`divisibleByThree: int -> bool`，以使当n为3的倍数时，`divisibleByThree` `n`为`true`，否则为`false`。注意：程序中不能使用取余函数`'mod'`。**

  ```sml
  (* divisibleByThree : int -> bool *)
  (* REQUIRES: n>=0 *)
  (* ENSURES: divisibleByThree n evaluates to true if n is a multiple of 3 and to false otherwise *)
  ```

  > **`ans`**
  >
  > ```sml
  > (* test 4 *)
  > (* divisibleByThree  :  int -> bool *)
  > (* REQUIRES :  n >= 0 *)
  > (* ENSURES :  divisibleByThree n evaluates to true if n is a multiple of 3 and to false otherwise *)
  > 
  > fun divisibleByThree (0 : int) : bool = true
  >     | divisibleByThree(1 : int) : bool = false
  >     | divisibleByThree(2 : int) : bool = false
  >     | divisibleByThree(n : int) : bool =
  >     if n < 0 then divisibleByThree(abs(n))
  >     else divisibleByThree(n - 3);
  > ```

+ **5. 函数`evenP`为偶数判断函数，即当且仅当该数为偶数时返回`true`。其代码描述如下**

  ```sml
  (* evenP : int -> bool 		*)
  (* REQUIRES: n >= 0 		*)
  (* ENSURES: evenP n evaluates to true iff n is even. *)
  fun evenP (0 : int) : bool = true
  	| evenP 1 = false
  	| evenP n = evenP (n - 2)
  ```

  **试编写奇数判断函数`oddP: int -> bool`，当且仅当该数为奇数时返回`true`。注意：代码不要调用函数`evenP`或`mod`。**

  > **`ans`**
  >
  > ```sml
  > (* test 5 *)
  > (* evenP : int -> bool *)
  > (* REQUIRES : n >= 0 *)
  > (* ENSURES : evenP n evaluates to true iff n is even. *)
  > fun evenP (0 : int) : bool = true
  > 	| evenP 1 = false
  > 	| evenP n = evenP(n - 2)
  > 
  > (* oddP : int -> bool *)
  > (* REQUIRES : n >= 0 *)
  > (* ENSURES : oddP n evaluates to true iff n is odd. *)
  > fun oddP (0 : int) : bool = false
  > 	| oddP(1 : int) : bool = true
  > 	| oddP n = oddP(n - 2);
  > val a=7;
  > val b=oddP(a);
  > ```

+ **6. 编写函数 interleave: int list * int list -> int list，该函数能实现两个int list数据的合并，且两个list中的元素在结果中交替出现，直至其中一个int list数据结束，而另一个int list数据中的剩余元素则直接附加至结果数据的尾部。如：**

  ```sml
  interleave([2],[4]) = [2,4]
  interleave([2,3],[4,5]) = [2,4,3,5]
  interleave([2,3],[4,5,6,7,8,9]) = [2,4,3,5,6,7,8,9]
  interleave([2,3],[ ]) = [2,3]
  ```

  > **`ans`**
  >
  > ```sml
  > (* test 6 *)
  > (* 实现两个int list数据的合并，且两个list中的元素在结果中交替出现，直至其中一个int list数据结束，而另一个int list数据中的剩余元素则直接附加至结果数据的尾部 *)
  > fun interleave(L1, []) = L1
  >     | interleave([], L2) = L2
  >     | interleave(x::L1, y::L2) = x::y::interleave(L1, L2);
  > val a = [1, 3, 5];
  > val b = [2, 4, 6, 7];
  > val c = interleave(a, b);
  > ```

+ **7.  编写函数reverse和reverse' ，要求：**

  **①函数类型均为：int list->int list，功能均为实现输出表参数的逆序输出；**

  **②函数reverse不能借助任何帮助函数；函数reverse’可以借助帮助函数，时间复杂度为O(n)。**

  > **`ans`**
  >
  > ```sml
  > (* test 7 *)
  > (* 实现输出表参数的逆序输出 *)
  > fun reverse([]) = []
  >     | reverse(x::L) = reverse(L) @ [x]
  > val a = [1, 2, 3, 4, 5];
  > val b = reverse(a);
  > 
  > (* 实现输出表参数的逆序输出 *)
  > fun reverse' ([], y) = y
  >     |reverse' (x::L, y) = reverse'(L, x::y);
  > 
  > val a = [1, 2, 3, 4, 5];
  > val b = reverse'(l1);
  > ```

+ **8. 给定一个数组`A[1..n]`, 前缀和数组`PrefixSum[1..n]`定义为：**

  **`PrefixSum[i] = A[0]+A[1]+...+A[i-1]；`**例如：

  ```sml
  PrefixSum [ ] = [ ]
  PrefixSum [5,4,2] = [5, 9, 11]
  PrefixSum [5,6,7,8] = [5,11,18,26]
  ```

  **试编写：**

  **(1)函数`PrefixSum: int list -> int list`，**

  **要求：`W*PrefixSum*(n) = O(n2)`。(n为输入`int list`的长度)**

  **(2) 函数`fastPrefixSum: int list -> int list`，**

  **要求：` W*fastPrefixSum*(n) =O(n)`. **

  **(提示：可借助帮助函数`PrefixSumHelp`)**

  > **`ans`**
  >
  > ```sml
  > (* test 8 *)
  > fun helper (a, []) = []
  >  	| helper(a, b::A) = (a+b)::helper(a, A)
  > fun PrefixSum [] = []
  >  	| PrefixSum (a::L) = a::helper(a, PrefixSum(L))
  > 
  > fun fastPrefixSum [] = []
  > 	| fastPrefixSum [x] = [x]
  > 	| fastPrefixSum (x::y::L) = x::fastPrefixSum((x + y)::L)
  > ```