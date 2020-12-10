-- simplest way is to enumirate the data
data Buul = Myfalse | Mytrue | Notsure
  deriving (Eq) -- allows checking of equality , default behavoir

data Day = Sun | Mon | Tue | Wed | Thu | Fri | Sat
  deriving (Eq, Show, Ord) -- allows checking of equality , default behavoir is Sun == Sun = True
  -- also allows for showing the type
  -- Ord bring the default order Sun < Mon < Tue ...

nextday :: Day -> Day
nextday Sun = Mon -- and so on

data Shape
  = Circle Float --
  | Square Float
  | Rectangle Float Float -- each possible type can take differnet inputs
  deriving (Eq, Show, Ord)

-- equality is checked on both types and the values of Float

area :: Shape -> Float
area (Circle r) = pi * r * r
area (Square s) = s * s
area (Rectangle h w) = h * w

weekend :: Day -> Bool
weekend Sat = True
weekend Sun = True
weekend _ = False

-- a good way to define is

data Person = Person {name :: String, age :: Int, height :: Float, phone :: String} deriving (Show)

-- name :: are just fucntion which give this valie

-- stack

type Stack = [a]

{-
-- another way to define this by hidig the internal representaion is by
data Stack = Stack [a]
  deriving (Show)
empty :: Stack
empty = Stack []

push :: a -> Stack -> Stack
push x ( Stack xs ) = Stack (x:xs)

pop :: Stack (a, Stack)
pop Stack (x:xs) = (x,Stack xs)

isempty :: Stack -> Bool
isempty (Stack []) = True
isempty (Stack _) = False

-}

push :: a -> Stack -> Stack
push x s = x : s

pop :: Stack -> (a, Stack)
pop (x : sp) = (x, sp)

insert :: a -> Int -> Stack -> Stack
insert x i s = (take (i -1) s) ++ [x] + (drop (n -1) s)

-- stack end

-- Queue

data Queue a = Queue [a]

empty :: Queue a
empty = Queue []

isempty :: Queue a -> Bool
isempty (Queue []) = True
isempty (Queue _) = False

-- O(n^2) time

enqueue :: a -> Queue a -> Queue a
enqueue x (Queue xs) = Queue (xs ++ [x])

dequeue :: Queue a -> (a, Queue a)
dequeue (Queue (x : xs)) = (x, Queue xs)

-- end queue

-- efficient queue

main = do
  print $ weekend Sat
  print $ weekend Wed
  print $ Sat
  print $ Square 9.0
  print $ area $ Square 9.0
  print $ Circle 9.0
  print $ area $ Circle 9.0
  print $ Rectangle 1.0 9.0
  print $ area $ Rectangle 1.0 9.0
  print $ Circle 9.0 == Square 9.0
  let guy = Person {name = "dfh", age = 21, height = 5.8, phone = "hfhsf"}
  print $ guy
  print $ s