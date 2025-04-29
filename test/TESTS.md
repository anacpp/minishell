# Test Instructions

### Readline

#### How to Compile and Run

To compile the `test_readline.c` file, use the following command:

````sh
cc -Wall -Wextra -Werror test_readline.c -lreadline -o test_readline

After compiling, run the program with:

```sh
./test_readline
````

#### What to Test

-   Prompt Display: Verify that the prompt (test$ ) appears when the program runs.
-   Input Echo: Type something and check if it prints back as Você digitou: ....
-   History Navigation: Use the up arrow key to confirm that previous commands appear in the history.
-   Exit with Ctrl+D: Press Ctrl+D to ensure the program exits the loop gracefully.
