# Tense
A fast, multi-threaded simple to use matrix library

# Usage
## Microsoft Visual Studio
1) Go to **Project Properties**
2) Find the field **Additional Dependencies**
3) Add TenseLib.lib 
   ```cpp
   TenseLib.lib
   ```
4) Navigate to **Configuration Properties → VC++ Directories**
5) Under **Library Directories**, add the path where /build is located.
6) Under **Include Directories**, add the path where /include is located.
# Results
Time required while multiplying 2 matrices of sizes (500,400) and (400,300)

<img width="470" alt="image" src="https://github.com/user-attachments/assets/64fb7178-c576-4027-ac3f-b83298f3365e" />

Hence we observer around **85%** reduction in time taken to compute the matrix product.
