# Mathematical operation parser

This is an implementation of parsing an expression of binary operations:
addition, subtraction, multiplication and division. It kind of implements
the **PEMDAS** except for **PE** part.

> **PEMDAS:** Stands for _Parenthesis_, _Exponents_, _Multiplication_,
> _Division_, _Addition_ and _Subtraction_. It represents the correct
> order of operations.

## Workings

- **Input:** It will take the valid input expression as a `string`.

- **Output:** It will give an output of `double` type after calculating
  the value of the expression in correct order.

## Constraints
1. This will support only `Multiplication (*)`, `Division (/)`, `Addition (+)`
   and `Subtraction (-)` as mentioned above.

2. Preceeding or ending with any operator in an expression will be
   considere as an invalid expression.
    
    **`x*y+z/` :** Invalid expression
    
    **`x*y+z` :** Valid expression

3. No white space shall contain in the expression, otherwise it will be an
   invalid expression.

4. The non operator characters shall not be any variable, it must be an
   integer or a decimal value.

5. No incomplete decimal point values shall be provided, otherwise it would
   be an invalid expression.

    **`33.` :** Invalid number

    **`.33` :** Invalid number

    **`33.0` :** Valid number

    **`0.33` :** Valid number


> _**Important Note:** I doubt that this algorithm will work for very large inputs.
> Since I am using recursion and it has a (very high) chance to use up the whole
> system stack and run into stack overflow. But anyways, I will hold on to this algo
> for now until it becomes very necessary to implement this also for some reason._