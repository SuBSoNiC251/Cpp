<!-- Got it. No fluff. Let’s go **from scratch**, and I’ll **speak declarations out loud**, **character by character**, show **how the compiler binds symbols**, and give you **multiple correct/incorrect variants** with *why*. Then we’ll do a **debug checklist** you can run on any pointer/array code.

--- -->

# How to read C declarations (clockwise / spiral rule)

**Rule you’ll use every time:**

1. **Find the identifier** (the variable name).
2. From there, read **outward**, preferring the **right** side first.
3. **`[]` and `()` bind tighter than `*`** in declarations.
4. Parentheses **force grouping**.

### What symbols mean (declaration vs expression)

| Symbol | In a **declaration**                         | In an **expression**           |
| ------ | -------------------------------------------- | ------------------------------ |
| `*`    | “pointer to …” (binds looser than `[]`/`()`) | “dereference” (follow pointer) |
| `[]`   | “array of …”                                 | “subscript” (indexing)         |
| `()`   | “function returning …” **or** group          | “call” **or** group            |
| `&`    | *(not used)*                                 | “address of”                   |

---

# Read these out loud with me

I’ll show the code, then how to **say it** exactly.

### 1) `int *p;`

* Start at `p`.
* Left is `*` → “p is **pointer to** …”
* Right nothing else, base type `int`.
* **Say:** “`p` is a pointer to int.”

### 2) `int **pp;`

* `pp` → left `*`, left again `*`.
* **Say:** “`pp` is a pointer to pointer to int.”

### 3) `int a[10];`

* `a` → right `[]` → “array of 10 …”
* Base type `int`.
* **Say:** “`a` is an array of 10 ints.”

### 4) `int *a[10];`

* `a` → right `[]` → “array of 10 …”
* left `*` (applies to the element type, not to `a` itself!) → “pointer to …”
* **Say:** “`a` is an array of 10 pointers to int.”

> Note why: `[]` binds tighter than `*`. So this is an array **of** pointers.

### 5) `int (*a)[10];`

* `a` is inside `()` so handle inside first.
* Left of `a` is `*` → “pointer to …”
* Outside right of `()` is `[]` → “… array of 10 …”
* Base type `int`.
* **Say:** “`a` is a pointer to an array of 10 ints.”

> Parentheses flipped it from “array of pointers” to “pointer to array”.

### 6) `int (*f)(double, char);`

* `f` inside `()` with `*` → “pointer to …”
* Right outside `()` is `(double, char)` → “function taking (double, char) and returning …”
* Base type `int`.
* **Say:** “`f` is a pointer to a function taking (double, char) and returning int.”

### 7) `int (*arr)[cols]`

* Same pattern as #5.
* **Say:** “`arr` is a pointer to an array of `cols` ints.”

This is the **correct** way to accept a contiguous 2D array *row pointer*.

### 8) `int arr[rows][cols];`

* Read as: `arr` is an array of `rows` … each element is an array of `cols` ints.
* **Say:** “`arr` is an array of `rows` arrays of `cols` ints.”

### 9) `int **arr;`

* **Say:** “`arr` is a pointer to pointer to int.”
* ❗ Not the same layout as `int arr[rows][cols]`. This fits **jagged** (array of pointers) or double indirection from `malloc`, **not** a contiguous 2D array parameter.

---

# Why your matrix function broke

Your code had:

```c
void create_matrix(int *arr[], int rows, int cols);
```

**Read it aloud:** “`arr` is an array of pointers to int.”
But you passed `int arr1[rows][cols]`, whose decayed type is **`int (*)[cols]`** (pointer to array-of-`cols`-int).
Mismatch → undefined behavior.

**Correct signatures (any of these):**

```c
void create_matrix(int rows, int cols, int arr[rows][cols]);
void create_matrix(int rows, int cols, int (*arr)[cols]);
void create_matrix(int rows, int cols, int arr[][cols]); // rows deduced, cols needed
```

**Wrong** for contiguous 2D:

```c
void create_matrix(int **arr, int rows, int cols); // ❌ layout mismatch
```

---

# Declarations you’ll meet a lot (spoken precisely)

### Arrays & pointers

```c
char s[20];          // “s is an array of 20 char.”
char *t;             // “t is a pointer to char.”
char *names[5];      // “names is an array of 5 pointers to char.”
char (*row)[20];     // “row is a pointer to an array of 20 char.”
```

### Const placement (read exactly)

```c
const int *p;        // “p is a pointer to const int.” (you can move p, not *p)
int const *p;        // same as above
int * const p = &x;  // “p is a const pointer to int.” (p fixed, *p mutable)
const int * const p; // “p is a const pointer to const int.”
```

### Function pointers (classic)

```c
int (*fp)(int, int); // “fp is a pointer to function (int,int) returning int.”
int *f(int, int);    // “f is a function taking (int,int) returning pointer to int.”
```

### Mixes that confuse people

```c
int *a[10];          // array of 10 pointers to int
int (*a)[10];        // pointer to array of 10 ints
int (*a[10])(void);  // array of 10 pointers to functions returning int
```

---

# The same characters mean different things depending on context

| Char | In **declarations** | In **expressions** |
| ---- | ------------------- | ------------------ |
| `*`  | pointer-to          | dereference        |
| `[]` | array-of            | subscript          |
| `()` | function-of / group | call / group       |
| `&`  | *(not used)*        | address-of         |

**Binding difference is the key trap**: `[]`/`()` bind tighter than `*` **only in declarations**.
That’s why `int *a[10];` is an **array of pointers**, not a pointer to array.

---

# Arrays + functions: what decays, what doesn’t

* In most expressions, `arr` (array) **decays** to `&arr[0]` (pointer to first element).
* Function parameters declared as `int arr[]` or `int arr[10]` are **actually** `int *arr` inside the function.
* A 2D parameter `int arr[][cols]` **decays** to `int (*)[cols]`.

**Why your `sizeof` trick failed:** inside a function parameter, `arr` is a pointer → `sizeof(arr)` gives pointer size, not array length.

---

# How to pass a 2D matrix (three correct ways)

Assume `int a[rows][cols];`

1. Carry the sizes:

```c
void f(int rows, int cols, int a[rows][cols]);
```

2. Use pointer-to-array:

```c
void f(int rows, int cols, int (*a)[cols]);
```

3. Fixed compile-time second dimension:

```c
#define COLS 4
void f(int a[][COLS], int rows);
```

**Do not** use `int **a` unless you allocated a “jagged” structure (array of `int*` to rows).

---

# Debugging checklist (use this every time)

1. **Print types in your head** using the spiral rule. If it says “array of pointers” but you intended “pointer to array”, fix with parentheses.
2. **Check parameter decay**: Inside functions, raw `arr` is a pointer. Don’t do `sizeof(arr)/sizeof(arr[0])` unless it’s a true array in the same scope.
3. **Prove your strides**: For a 2D `int a[rows][cols]`, verify that `&a[i+1][0] == &a[i][0] + cols`.
4. **Print addresses**:

   ```c
   printf("%p %p %p\n", (void*)a, (void*)a[0], (void*)&a[0][0]);
   ```

   For contiguous 2D, `a` and `&a[0]` differ in type but point to same location; `a[1]` should be `cols*sizeof(int)` ahead.
5. **For loops**: double-check the loop variables in the conditions: `for (int j = 0; j < cols; j++)` (you used `i < cols`—classic bug).
6. **Match signature and call**: If parameter is `int (*arr)[cols]`, **pass** just `arr` (not `&arr`).

---

# Your matrix signatures—spoken precisely

```c
void create_matrix(int rows, int cols, int arr[rows][cols]);
```

> “`create_matrix` takes (rows, cols, `arr` which is an array of `rows` arrays of `cols` ints).”

```c
void create_matrix(int rows, int cols, int (*arr)[cols]);
```

> “`create_matrix` takes (rows, cols, `arr` which is a pointer to an array of `cols` ints).”

**Both are correct** and equivalent at the call site.

**Your original:**

```c
void create_matrix(int *arr[], int rows, int cols);
```

> “`arr` is an array of pointers to int.”
> **Not** the same shape as a contiguous `rows×cols` matrix.

---

# Micro-drills (rapid-fire)

Read these out loud exactly:

1. `double *v[3];`
   → “`v` is an array of 3 pointers to double.”

2. `double (*v)[3];`
   → “`v` is a pointer to an array of 3 doubles.”

3. `char * const p;`
   → “`p` is a const pointer to char.”

4. `const char *p;`
   → “`p` is a pointer to const char.”

5. `int (*g[5])(void);`
   → “`g` is an array of 5 pointers to functions returning int.”

6. `int *(*h)[7];`
   → “`h` is a pointer to an array of 7 pointers to int.”

If you can read all six cleanly, you’re **fluent**.

---

# Why `int **` ≠ 2D array (in practice)

* `int arr[R][C]` is **one big contiguous block**. Type decays to `int (*)[C]`.
* `int **p` usually points to a **pointer** that points to **pointers**, each of which may point to **separately allocated rows**. No guarantee of contiguity or stride `C`.

So `p[i][j]` only works if you **constructed** that structure (allocate `R` pointers, then `R` separate `C`-sized int blocks). It will not magically match `arr`.

---

# Final: a tiny “self-debug ritual” for your matrix code

1. Fix the signature:

   ```c
   void print_matrix(int r, int c, int a[r][c]);
   // or int (*a)[c]
   ```

2. Verify loops:

   ```c
   for (int i = 0; i < r; i++)
     for (int j = 0; j < c; j++)
       printf("%d ", a[i][j]);
   ```

3. Never do `sizeof(a)` in that function to get dimensions.

4. When in doubt, print addresses:

   ```c
   printf("a=%p a[0]=%p &a[0][0]=%p\n",
          (void*)a, (void*)a[0], (void*)&a[0][0]);
   printf("&a[1][0] - &a[0][0] = %td ints\n",
          (&a[1][0] - &a[0][0]));
   ```

You’ll **see** `cols` show up in that last difference if it’s contiguous.

---

If you want, throw me any declaration you’re unsure about, and I’ll **speak it aloud** and show 1–2 equivalent rewrites, plus one **nearby wrong** form and why it’s wrong. That way you’ll train your eye to spot the exact binding every time.
