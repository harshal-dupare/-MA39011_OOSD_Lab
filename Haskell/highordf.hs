 


newmap :: (a -> b) -> [a] -> [b]
newmap f [] = []
newmap f (x:xs) = (f x):(newmap f xs)

is_even :: Int -> Bool
is_even x = mod x 2 == 0

is_alot :: Float -> Bool
is_alot x = x > 5.5

newfilter :: (a -> Bool) -> [a] -> [a]
newfilter p [] = []
newfilter p (x:xs)
      | p x = x : (newfilter p xs)
      | otherwise = newfilter p xs

my_filter :: [Int] -> [Int]
my_filter [] = []
my_filter (x : xs)
    | mod x 2 == 0 = x : (my_filter xs)
    | otherwise = my_filter xs

main = do 
    let l1 = [6,8..20] -- considers numbers till the last number, with common difference indicated by first two numbers
    let l2 = []
    let l3 = [3,2,10,7,41,8,13]
    let l4 = [7.2,3.0,4.7, 1.24,5.5, 5.6]
    print $ l1
    print $ map (+3) l1
    print $ map (+3) []
    print $ newmap (+3) l1
    print $ newmap (*2) l1
    print $ filter is_even l3
    print $ newfilter is_even l3
    print $ my_filter l3
    print $ newfilter is_alot l4
    print $ foldr (+) 2 l3
