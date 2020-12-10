{-
Harshal Dupare | 18MA20015
1) Extend the natural numbers "Nat" datatype defined in class to integers, by introducing user defined signs.
 Define addition, multiplication and convert to int, 
for your new datatype, so that the functions may now accommodate negative integers too. 
Define a new subtraction function as well.
-}


{-Nat is the new data type and the starting letter of this name is a -}
data Nat = Zero | Succ Nat -- 1st it can be 0 or succ of Nat number
    deriving Show
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

-- to multiply
multiply :: Nat-> Nat -> Nat
multiply Zero _ = Zero
multiply _ Zero = Zero
multiply x (Succ (y)) = plus x (multiply x y)

-- int data type
data Zint = Zint Nat Int
    deriving Show

-- main addition fucntion
addzint :: Zint -> Zint -> Zint
addzint (Zint Zero _) x = x -- if any zero return same 
addzint x (Zint Zero _) = x
addzint (Zint n sgn) (Zint m sgm)
    | sgn == sgm = (Zint (plus n m) sgn) -- if same sign then
    | (contoint n) > (contoint m) = (Zint (minus n m) (sgn)) -- take the greater and subtract it from it
    | otherwise = (Zint (minus m n) ((-1)*sgn))


-- to multipluy intergers
multzint :: Zint -> Zint -> Zint
multzint (Zint Zero _) _ = Zint Zero 1 -- if any is zero
multzint _ (Zint Zero _) = Zint Zero 1
multzint (Zint n sgn) (Zint m sgm) = (Zint (multiply n m) (sgn*sgm)) -- just multiplty the magnitude ans the sign

subzint :: Zint -> Zint -> Zint
subzint (Zint Zero _) x = x
subzint x (Zint Zero _) = x
subzint (Zint n sgn) (Zint m sgm) = addzint (Zint n sgn) (Zint m ((-1)*sgm)) -- sub the greater from smaller

-- convert to int 
zconvtoint :: Zint -> Int
zconvtoint (Zint Zero _) = 0 -- if zero 
zconvtoint (Zint x sgn) = (sgn)*(contoint x) -- just get the magniute and the int sign


main = do  
    let x = plus (Succ Zero) (Succ Zero)
    let y = plus x x 
    let z = plus y y
    let d = plus x (Succ Zero)
    let zz = Zint d 1
    let zzz = Zint d (-1)
    print $ zconvtoint zz
    print $ zconvtoint zzz
    let z1 = multzint zz zzz
    print $ zconvtoint z1
    let z2 = addzint zz z1
    print $ zconvtoint z2
    let z3 = subzint z2 z1
    print $ zconvtoint z3
    let z4 = multzint z1 z2
    print $  zconvtoint z4