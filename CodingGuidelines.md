# Introduction #

With any large project, some form of consistency is required.  Feel free to add a comment below if you think that the style guidelines should be changed.

# Comments #

Use multi-line comments for long discussions and the header.  Use C++ style (i.e. ` // `) comments for commenting out code, short discussions, and one-line comments.

# Whitespace #

## Indentation ##

Every block of code should be indented four spaces, and tabs should not be used.  Try to see if your code editor can automatically insert spaces when you hit tab.

## Curly Braces ##

Use the [Allman style](http://en.wikipedia.org/wiki/Indent_style#Allman_style) of curly brace positioning; put the opening curly brace on the line after the statement and indented to the same level as the statement.

```
int main(int argc, char **argv)
{
    if (x == 4)
    {
        // ...
    }
    else
    {
        // ...
    }
    return 0;
}
```

## Extra Whitespace ##

  * One space should be placed after the commas between arguments given to a function
  * One space should be placed before and after all binary operators except:
    * ` . `
    * ` -> `
  * No space between the function name and the opening parenthesis
  * One space between keywords like ` if ` and the opening parenthesis
  * No space padding the inside of parentheses

# Naming #

| **Element** | **Style** | **Example** |
|:------------|:----------|:------------|
| Preprocessor | Underscore-delimited uppercase | MY\_MACRO   |
| Constant    | k + Upper camel case | kMyConstant |
| Variable    | Lower camel case | terrificVariable |
| Function    | Lower camel case | awesomeFunction |
| struct/typedef | Underscore-delimited lowercase | my\_great\_type |
| Class       | Upper camel case | MySuperClass |
| Instance variable | Lower camel case | spamEggsSpamAndSpam |
| Instance method | Upper camel case | GreatMethod |

## Example ##

```
#define MY_MACRO

extern const int kMyFoo;
extern double bigGlobal;

void myFunction(double, double);

typedef unsigned char custom_byte;

class FooBaz
{
private:
    int spam;
public:
    Foo(int);
    Foo ReturnAnotherFoo(int);
};
```

# Miscellaneous #

  * Try to put as much of the program's custom functions, variables, and classes into the namespace ` CrabBattle `.
  * When breaking a long conditional at the logical operator (like ` && `), put the operator at the end of the line