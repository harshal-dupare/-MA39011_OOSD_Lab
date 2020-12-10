data List a = Nil | Cons a (List a) -- reccursive definations
{-it says that list can be Nil or it can contain a constant and have its own 
in the defination
-}

{-Nat is the new data type and the starting letter of this name is a -}
data Nat = Zero | Succ Nat | Pred Nat-- 1st it can be 0 or succ of Nat number
{-succ ( a function name ) is a function which recursisively deifnes the data-}

{-plus function defining the string manuplation of the data type-}
plus :: Nat -> Nat -> Nat
plus x Zero = x
plus Zero x = x
plus n (Succ (m)) = Succ (plus n m) -- reccursion def of plus function using succ function

contoint :: Nat -> Int -- note cant use "_" in variable names
contoint Zero = 0
contoint (Succ (x)) = 1 + (contoint x)

multiply :: Nat-> Nat -> Nat
multiply Zero _ = Zero
multiply _ Zero = Zero
multiply x (Succ (y)) = plus x (multiply x y)



power :: Float -> Nat -> Float
power _ Zero = 1.0
power x (Succ n) = x * power x n -- Cons is the next element

newhead :: List a -> a
newhead Nil = error "List is empty"
newhead (Cons x (_)) = x


main = do  
    let l1 = [1..5]
    print $ l1
    print $ newhead (Cons 4 (Cons 3 (Cons 2 ( Nil ))))
    print $ power 3 (Succ (Succ (Succ Zero)))
    let x = plus (Succ Zero) (Succ Zero)
    let y = plus x x 
    let z = plus y y
    print $ power 2.2 z
    let d = plus x (Succ Zero)
    print $ contoint z
    print $ contoint d
    print $ contoint ( multiply z d ) -- note we cant print Nat as it has now show function