# multiTypeTree

**usage**:

"**multiTypeTree -i input -o output**" for launching described in the terms of reference

"**multiTypeTree -t**" to run with test cases

**In the test**:
1) Create a test tree.
2) Serialize it to a file.
3) Deserialize the file into a new tree.
4) Compare the original tree with the received one, expect that all their nodes are equal.
5) Create another tree and compare it with the one subtracted from the file, expect that their nodes will be different.
