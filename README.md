# Autocomplete
This project implements a fast autocomplete functionality.
The autocomplete task is to quickly retrieve the top terms that match a query string. For example, if the query string is "Eng", you matches might be "English",
"Engineering", and "EngSci".

To accomplish the task, the following steps were taken:
  - Read in the entire file of terms, and sort the terms in lexicographic ordering. This sorted list will be reused for multiple queries.
  - Use binary search to find the location of the first term in lexicographic ordering that matches the query string, as well as the last term in lexicographic oredering that matches the query string.
  - Extract the terms that match the query string, and sort them by weight.
  - Extract the top matching terms by weight.
