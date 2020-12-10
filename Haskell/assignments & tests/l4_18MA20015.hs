{-
Harshal Dupare | 18MA20015
13-11-20

[1] Extend the natural numbers "Nat" datatype defined in class to integers, by introducing user defined signs.
 Define addition, multiplication and convert to int, for your new datatype,
  so that the functions may now accommodate negative integers too. Define a new subtraction function as well.  [10 marks]

[2] Use the datatype for integers defined in the previous question to define a datatype for rational numbers.
Define addition, subtraction, multiplication and division, and a function to print your rational numbers.
All the functions should finally give rational numbers in their simplest form. [20 marks]

-}

-- natural number data

{-Nat is the new data type and the starting letter of this name is a -}
data Nat = Zero | Succ Nat -- 1st it can be 0 or succ of Nat number
  deriving (Show)

{-succ ( a function name ) is a function which recursisively deifnes the data-}

{-plus function defining the string manuplation of the data type-}
plus :: Nat -> Nat -> Nat
plus x Zero = x
plus Zero x = x
plus n (Succ (m)) = Succ (plus n m) -- reccursion def of plus function using succ function

-- sub smaller from grater
minus :: Nat -> Nat -> Nat
minus x Zero = x
minus Zero x = x
minus (Succ (n)) (Succ (m)) = minus n m -- reccursion def of plus function using succ function

-- to convert to int
contoint :: Nat -> Int -- note cant use "_" in variable names
contoint Zero = 0
contoint (Succ (x)) = 1 + (contoint x)

-- to multiply natural numbers
multiply :: Nat -> Nat -> Nat
multiply Zero _ = Zero -- if any zero
multiply _ Zero = Zero
multiply x (Succ (y)) = plus x (multiply x y)

-- natural number data data

-- integers number data

-- int data type
data Zint = Zint Nat Int
  deriving (Show)

-- main addition fucntion
addzint :: Zint -> Zint -> Zint
addzint (Zint Zero _) x = x -- if any zero return same
addzint x (Zint Zero _) = x
addzint (Zint n sgn) (Zint m sgm)
  | sgn == sgm = (Zint (plus n m) sgn) -- if same sign then
  | (contoint n) > (contoint m) = (Zint (minus n m) (sgn)) -- take the greater and subtract it from it
  | otherwise = (Zint (minus m n) ((-1) * sgn))

-- to multipluy intergers
multzint :: Zint -> Zint -> Zint
multzint (Zint Zero _) _ = Zint Zero 1 -- if any is zero
multzint _ (Zint Zero _) = Zint Zero 1
multzint (Zint n sgn) (Zint m sgm) = (Zint (multiply n m) (sgn * sgm)) -- just multiplty the magnitude ans the sign

-- to subtract integers
subzint :: Zint -> Zint -> Zint
subzint (Zint Zero _) x = x
subzint x (Zint Zero _) = x
subzint (Zint n sgn) (Zint m sgm) = addzint (Zint n sgn) (Zint m ((-1) * sgm)) -- sub the greater from smaller

-- convert to int
zconvtoint :: Zint -> Int
zconvtoint (Zint Zero _) = 0 -- if zero
zconvtoint (Zint x sgn) = (sgn) * (contoint x) -- just get the magniute and the int sign

-- to convert into to Nat
inttoNat :: Int -> Nat
inttoNat 0 = Zero
inttoNat n = (Succ (inttoNat (n -1)))

-- to convert into to zint
inttozint :: Int -> Zint
inttozint 0 = (Zint Zero 1)
inttozint n
  | n < 0 = (Zint (inttoNat ((-1) * n)) (-1))
  | otherwise = (Zint (inttoNat (n)) 1)

-- integers number data end

-- rational number data

-- data type to store rational number
data Ratn = Ratn Zint Zint Int -- 2 integers and sign
  deriving (Show)

-- -- to get gcd of integers
-- gcd :: Int -> Int -> Int
-- gcd x 0 = x
-- gcd 0 x = x
-- gcd x y = gcd y (x `mod` y)

-- -- to get gcd of zint
-- zgcd :: Zint -> Zint -> Zint
-- zgcd x y = gcd (zconvtoint x) (zconvtoint y)

-- gives the sign of the number  (sx*x + sy*y) where both x , y >= 0
getsign :: Int -> Int -> Int -> Int -> Int
getsign x y sx sy
  | sx == sy = sx -- if both have same sign return that sign
  | x > y = sx -- if any has different sign return the sign of larger one
  | otherwise = sy

-- to add rational numbers
radd :: Ratn -> Ratn -> Ratn
radd (Ratn (Zint Zero _) _ _) x = x -- if any zero return the other number
radd x (Ratn (Zint Zero _) _ _) = x -- if any zero return the other number
radd (Ratn p1 q1 s1) (Ratn p2 q2 s2) = (Ratn p3 q3 s3)
  where
    -- get the two terms in numerator
    n1 = multzint p1 q2
    n2 = multzint p2 q1
    -- get the denominator
    d = multzint q1 q2
    -- get the numerator
    n = addzint n1 n2
    in1 = zconvtoint n1
    in2 = zconvtoint n2
    -- get the sign of the new rational number
    s3 = getsign in1 in2 s1 s2
    -- simplify the new rational number
    ip = zconvtoint n
    iq = zconvtoint d
    gpq = gcd ip iq
    fp = div ip gpq
    fq = div iq gpq
    -- get the final rational number
    p3 = inttozint fp
    q3 = inttozint fq

-- to subtract rational numbers
rsub :: Ratn -> Ratn -> Ratn
rsub (Ratn (Zint Zero _) _ _) (Ratn pp qq ss) = (Ratn pp qq ((-1) * ss)) -- if any is zero return the other number
rsub x (Ratn (Zint Zero _) _ _) = x
rsub (Ratn p1 q1 s1) (Ratn p2 q2 s2) = radd (Ratn p1 q1 s1) (Ratn p2 q2 ((-1) * s2)) -- just negate the 2nd rational number and add it

-- to multiply rational numebers
rmult :: Ratn -> Ratn -> Ratn
rmult (Ratn (Zint Zero _) _ _) _ = (Ratn (Zint Zero 1) (Zint (Succ Zero) 1) 1) -- if any rational is zero return zero with proper format
rmult _ (Ratn (Zint Zero _) _ _) = (Ratn (Zint Zero 1) (Zint (Succ Zero) 1) 1)
rmult (Ratn p1 q1 s1) (Ratn p2 q2 s2) = (Ratn p3 q3 (s1 * s2))
  where
    -- multiply using zint multiplication
    tp = multzint p1 p2
    tq = multzint q1 q2
    -- get gcd and use it to simplify the rational number
    ip = zconvtoint tp
    iq = zconvtoint tq
    gpq = gcd ip iq
    fp = div ip gpq
    fq = div iq gpq
    -- get the final ratios
    p3 = inttozint fp
    q3 = inttozint fq

-- to divide rational numbers
-- note divsion by zero is also defined as zero
rdiv :: Ratn -> Ratn -> Ratn
rdiv (Ratn (Zint Zero _) _ _) _ = (Ratn (Zint Zero 1) (Zint (Succ Zero) 1) 1) -- if any number is zero
rdiv _ (Ratn (Zint Zero _) _ _) = (Ratn (Zint Zero 1) (Zint (Succ Zero) 1) 1)
rdiv (Ratn p1 q1 s1) (Ratn p2 q2 s2) = rmult (Ratn p1 q1 s1) (Ratn q2 p2 s2) -- just reverse the 2nd rational number and multiply it

-- to convert
rattostr :: Ratn -> String
rattostr (Ratn (Zint Zero _) _ _) = "0" -- if zero then return zero
rattostr (Ratn p q s)
  | s == 1 = (show (zconvtoint p)) ++ "/" ++ (show (zconvtoint q)) -- if positive
  | otherwise = "-" ++ (show (zconvtoint p)) ++ "/" ++ (show (zconvtoint q)) -- if negative

-- rational number data

main = do
  -- tests for part 1
  print "Testing part 1"
  let x = plus (Succ Zero) (Succ Zero) -- x = 2
  let y = plus x x -- y = 4
  let z = plus y y -- z = 8
  let d = plus x (Succ Zero) -- d = 3
  let zz = Zint d 1 -- zz = 3
  let zzz = Zint d (-1) -- zzz = -3
  print $ zconvtoint zz -- prints 3
  print $ zconvtoint zzz -- prints -3
  let z1 = multzint zz zzz -- z1 = -9
  print $ zconvtoint z1 -- prints -9
  let z2 = addzint zz z1 -- z2 = -6
  print $ zconvtoint z2 -- prints -6
  let z3 = subzint z2 z1 -- z3 = -6-(-9) = 3
  print $ zconvtoint z3 -- prints 3
  let z4 = multzint z1 z2 -- z4 = (-9)*(-6) = 54
  print $ zconvtoint z4 -- prints 54
  -- tests end for part 1

  -- tests for part 2
  print "Testing part 2"
  let one = (Zint (Succ Zero) 1)
  let two = (Zint (Succ (Succ Zero)) 1)

  let r1 = (Ratn one two 1) -- r1 = 1/2
  print $ rattostr r1 -- prints 1/2
  let r2 = (Ratn two one (-1)) -- r2 = -2/1
  print $ rattostr r2 -- prints -2/1
  let r3 = rmult r1 r2 -- r3 = (-2/1)*(1/2) = (-1/1)
  print $ rattostr r3 -- prints -1/1
  let r4 = radd r2 r3 -- r4  = (-1/1)+(-2/1) = (-3/1)
  print $ rattostr r4 -- prints  -3/1
  let r5 = rdiv r3 r4 -- r5 = (-1/1)/(-3/1)
  print $ rattostr r5 -- prints 1/3
  let r6 = rsub r4 r5 -- r6 = (-3/1) - (1/3)
  print $ rattostr r6 -- prints -10/3
  -- tests end for part 2
