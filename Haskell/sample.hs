
-- list can be basically thought of as linked lists, where accessing an index may take O(n) time

-- Haskell also offers arrays where the access time is constant

import Data.Array

array1 = listArray (0,4) ['g','h', 'a','b','c']

array2 = listArray ('a','d') [3,5,9,1]

array3 = listArray ('a','d') [1..]

array4 = listArray (5,9) ['a','b','c','d','e']



main = do
 let l1 = [1..5]
 print $ l1
 print $ array1
 print $ array2
 print $ array3
 print $ l1 !! 1
 print $ array1 ! 3 -- constant time operator
 print $ array4 ! 6
 print $ range (1,3)
 print $ range ('f','n')
 print $ index (25,75) 30 -- finds the index of 30 in (25,75)
-- print $ index (25,75) 20 -- out of range! 
 print $ inRange (25,75) 30
 print $ inRange (25,75) 20
 print $ rangeSize (25,75)
 print $ bounds array1   -- gives the index bounds with which the array was constructed
 print $ bounds array2
 print $ indices array2 -- list of indices of the array
 print $ elems array1
 print $ assocs array1
 print $ (//) array1 [(3,'d')]  -- the array can be updated using the index
-- print $ (//) array1 [(5,'d')]  -- cannot go out of already set index bound