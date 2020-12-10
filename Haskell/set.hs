-- set data structure

data Set a = Set [a]
  deriving (Show)

search :: Eq a => a -> Set a -> Bool
search x (Set y) = elem x y

sinsert :: Eq a => a -> Set a -> Set a
sinsert x (Set y)
  | elem x y = Set y
  | otherwise = Set (x : y)

sdelete :: Eq a => a -> Set a -> Set a
sdelete x (Set y) = Set (filter (/= x) y) -- bianry fucntion in filter x is fixed argument

-- set is good but O(n) for each appear

-- sieve of eratosthenes

sieve :: [Int] -> [Int]
sieve [] = []
sieve (x : xs) = x : (sieve [y | y <- xs, (mod y x) > 0])

primes :: Int -> [Int]
primes 2 = [2]
primes n = sieve [2 .. (n)]

-- sieve of eratosthenes

-- merge sort

merge :: (Ord a) => [a] -> [a] -> [a]
merge [] t = t
merge t [] = t
merge (x : xs) (y : ys)
  | x <= y = (x : (merge xs (y : ys)))
  | otherwise = (y : (merge (x : xs) ys))

mergesort :: (Ord a) => [a] -> [a]
mergesort [] = []
mergesort [t] = [t]
mergesort x = merge ll rl
  where 
    ll = mergesort ( take (div (length x) 2) x ) 
    rl = mergesort ( drop (div (length x) 2) x ) 
-- merge sort



-- graphs 
-- enuminerate it
edge :: Char -> Char -> Bool
edge 'a' 'b' = True
edge 'a' 'c' = True
edge 'a' 'd' = True
edge _ _ = False

-- graphs

-- nqueens
nqueens :: Int -> [[Int]]
nqueens n = (iterate (extend n)[[]]) !! (n+1) 

extend :: Int -> [[Int]] -> [[Int]]
extend n [[]] = [[0]]

getqueen :: Int -> [Int]
getqueen n = head (nqueens n)

-- nqueens

main = do
  let l = [1, 2, 3]
  let s = Set l
  print $ s
  let q = sinsert 4 s
  print $ q
  let qq = sinsert 4 q
  print $ qq
  let q3 = sdelete 3 qq
  print $ q3
  print $ search 3 q3
  print $ search 3 q3
  print $ search 3 q
  let ll = [1, 2, 4, 8, 1, 3, 5, 2, -2, 4, 6, 0, 22, 43, 5, 5, 3, -2]
  let sl = mergesort ll
  print $ sl
  print $ ll
  print $ length sl
  print $ length ll