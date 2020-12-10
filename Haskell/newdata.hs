




data Nat = Zero | Succ Nat -- non negative integers

power :: Float -> Nat -> Float
power x Zero = 1.0
power x (Succ n) = x * power x n 

plus :: Nat -> Nat -> Nat 
plus m Zero = m 
plus m (Succ (n)) = Succ (plus m n)


{-
plus (Succ (Succ Zero) )  (Succ (Succ (Succ Zero) ))

= Succ ( plus  Succ (Succ Zero)    (Succ (Succ Zero) )     )

= Succ ( Succ ( plus  Succ (Succ Zero)   (Succ Zero)  ))


= Succ ( Succ ( Succ  (plus    Succ (Succ Zero)     Zero    ) ))

= Succ ( Succ ( Succ  (     Succ (Succ Zero)        ))


-}



mult :: Nat -> Nat -> Nat 
mult m Zero = Zero
mult m (Succ n) = plus m (mult m n)  -- m ( n + 1) = m + m*n



{-




-}

{-
convtoint :: Nat -> Int -- convert to int
convtoint Zero = 0  -- converts Zero (which is user defined) to actual 0
convtoint (Succ n) = 1 + (convtoint n) 
-}


data List a = Nil | Cons a (List a)

--  Cons 3 (Cons 2  ( Nil ))

newhead :: List a -> a 
newhead Nil = error "List is empty"
newhead (Cons x (_)) = x


main = do
 let l1 = [1..5]
 let n1 = (Succ (Succ Zero) )
 let n2 = (Succ (Succ (Succ Zero) ))
 print $ l1
 print $ newhead (Cons 4 (Cons 3 (Cons 2  ( Nil ))))
 print $ power 3.0 (Succ (Succ Zero) )
 --print $ convtoint (plus n1 n2)
 --print $ convtoint (mult n1 n2)

-- print $ plus 3 2
 


-- print $ (//) array1 [(5,'d')]  -- cannot go out of already set index bound