The used ADTs (Abstract Data Types) are:

1) Generic List ADT (Template <class T>) represented as an array.
2) Ordered Set ADT with generic elements (Template <class T>) represented as a binary search tree.
I used the first ADT to represent friendships and messages. Messages were better represented as an array to preserve their sending order, 
while friendships felt more natural to represent as an array, although they could have been represented as a binary search tree as well.
I used the second ADT to represent users, because it was more suitable in terms of execution time.
Users are accessed more frequently in the program and their traversal is less complex
