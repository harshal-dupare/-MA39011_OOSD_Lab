sqr :: Int -> Int -- type defination of function
sqr x = x*x -- computation rule

xor :: Bool -> Bool -> Bool -- type defination of function
xor x y = (y && (not x))||(x && (not y)) -- computation rule

inorder :: Int -> Int -> Int -> Bool
inorder x y z = (x <= y) && (y <= z)

{-
multiple def and patter matching
also we can enumirate the cases
-}
dxor :: Bool -> Bool -> Bool
dxor True False = True
dxor False True = True
dxor x y = False

dor :: Bool -> Bool -> Bool
dor True x = True
dor x True = True
dor x y = False

{-
dont care patterns
doesnt use the variable
"_" matches with everything in pattern matching
-}
dand :: Bool -> Bool -> Bool
dand True x = x
dand False _ = False

fact :: Int -> Int 
fact 0 = 1 -- note for neg numbers it will get into inf loop
fact n = n * (fact (n-1) ) -- note that () is required or else it will compute fact(n) - 1

{-conditional expression for enableing and disabeling defs,
 called as "gaurded conditional expression"-}
factorial :: Int -> Int
factorial 0 = 1 -- pattern match
factorial n
    | n ==0 = 1 -- direct guard condition for n = 0
    | n < 0 = n * (factorial (n+1)) -- condition is one by one evaluated and if this is true the def is used
    | n > 0 = n * (factorial (n-1))
{-note if we miss cases then it will throw error saying that "pattern match falure : pattern_case"-}

{-otherwise === else in normal langauge-}
fib :: Int -> Int
fib n
    | n == 0 = 1
    | n == 1 = 1
    | otherwise = ( fib (n-1) ) + ( fib (n-2) )

mygcd :: Int -> Int -> Int
mygcd 0 a = 0
mygcd a 0 = 0
mygcd 1 a = 1
mygcd a 1 = 1
mygcd a b
    | a >= b = mygcd b (mod a b)
    | otherwise = mygcd a (mod b a)


-- we need to run a loop for which we can use recursive def function divsearch
-- note that the order of the functions definations doesnt matter
largest_div :: Int -> Int
largest_div 1 = 1
largest_div n = divsearch n (n-1)


-- simulates a loop 
divsearch :: Int -> Int -> Int
divsearch 0 _ = 0
divsearch n k
    | (mod n k) == 0 = k
    | otherwise = divsearch n (k-1)



{-int partof the log_k(n)-}
intlog :: Int -> Int -> Int
intlog 1 _ = 0
intlog n k
    | n < k = 0
    | otherwise = 1 + ( intlog (div n k) k )

{-returns n^k-}
power :: Int -> Int -> Int
power _ 0 = 1
power n 1 = n
power n k
    | (mod k 2) == 1 = n * (( power n (div k 2) )^2)
    | otherwise =  (power n (div k 2))^2

{-reverse the digit-}
intreverse :: Int -> Int
intreverse n
    | n < 10 = n
    | otherwise = (mod n 10)*(power 10 (intlog n 10))+(intreverse (div n 10))

-- print pythogorian triplets from 1 to 100
{-

print $ [(x,y,z) | x<-[1..100], y<-[1..100], z<-[1..100], x*x + y*y == z*z]

-- unique
print $ [(x,y,z) | x<-[1..100], y<-[1..100], z<-[1..100], ( x*x + y*y == z*z )&&(x>=y)]

-}

isprime :: Int -> Bool
isprime 1 = False
isprime 2 = True
isprime k = ([] == [ x | x <- [2..((div k 2) + 1)], k `mod` x == 0])

printprime :: Int -> IO ()
printprime n = print $ [x | x <- [1..n], isprime x]
