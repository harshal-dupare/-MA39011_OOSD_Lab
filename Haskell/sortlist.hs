 

insert :: Int -> [Int] -> [Int] -- inserts an integer in its correct place in a sorted list 
insert x [] = [x]
insert x (y:ys)
    | (x <= y) = x:y:ys
    | (x>y) = y : (insert x ys)

isort :: [Int] -> [Int]
isort [] = []
isort (x:xs) = insert x (isort xs) -- inserts x into a sorted xs

merge :: [Int] -> [Int] -> [Int]
merge [] [] = []
merge l1 [] = l1
merge [] l2 = l2
merge (x : xs) (y : ys)
    | x <= y = x : merge xs (y : ys)
    | otherwise = y : merge (x : xs) ys

 
merge_sort :: [Int] -> [Int]
merge_sort [] = []
merge_sort[x] = [x]
merge_sort l = merge (merge_sort (take (div (length l) 2) l)) (merge_sort (drop (div (length l) 2) l))


main = do 
    let l1 = [20, 18.. 6] -- considers numbers till the last number, with common difference indicated by first two numbers
    let l2 = []
    let l3 = [3,2,10,7,41,8,13]
    let l4 = [7.2,3.0,4.7, 1.24,5.5, 5.6]
    print $ l1
    print $ isort l1
    print $ merge_sort l1
    print $ take 3 l3
    print $ drop 3 l3
 
