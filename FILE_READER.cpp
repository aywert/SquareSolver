//#include<TXLib.h>
#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
// ПРАТА!!!!!!!!!!!
// assert
// github
// README markdown/no HTML in github

// цветной вывод s

const double APROX = 1e-6;

enum CONST
{
    LEN_BUFFER  = 100,
    LEN_STR     =  10,
};

enum NRoots
{
    ZERO_SOLUT  =      0,
    ONE_SOLUT   =      1,
    ONE_SOLUTAO =      3,
    TWO_SOLUT   =      2,
    INF         =    999,
    NONE        =  10000,
};

enum SCANF_STATUS
{
    SUCCESS = 1,
    FAIL = 0,
};

enum GREETING_STATUS
{
    YES = 1,
    NO = 0,
};

enum COMPARE_STATUS
{
    EQUALE     = 1,
    NOT_EQUALE = 0,

};

enum BOOL
{
    TRUE = 1,
    FALSE = 0,
};

struct Roots
{
    double x1;
    double x2;
    int n_roots;
};

struct Coeffs
{
    double a;
    double b;
    double c;
};

struct Data // test data
{
    Coeffs coeffs;
    Roots  roots;
    Roots  roots_exp;
};

GREETING_STATUS start_greeting(void);
void start_tester(void);
void solve_square(void);
SCANF_STATUS scan_Coeffs(Coeffs* data);
void calculate_answer(Coeffs* ptr_coeff, Roots* ptr_root);
int return_n_root(Coeffs* ptr_coeffs, double* link_d);
void print_answer(Roots* ptr_roots);
void check_sample(Data All_tests);
COMPARE_STATUS compare(double var1, double var2);
BOOL is_quit(const char* ptr_buffer);

int main(void)
{
    if (start_greeting())
        start_tester();
    else
        solve_square();
}

void solve_square(void)
{
    Roots roots  = {};
    Coeffs coeff = {};

    assert(scan_Coeffs(&coeff) == SUCCESS);
    calculate_answer(&coeff, &roots);
    print_answer(&roots);
}

SCANF_STATUS scan_Coeffs(Coeffs* ptr_coeff)
{
    assert(ptr_coeff != NULL);

    double* ptr_a = &ptr_coeff->a;
    double* ptr_b = &ptr_coeff->b;
    double* ptr_c = &ptr_coeff->c;

    printf("enter 3 numbers - coefficients:\n");

    int ind = 0, curr_c = 0;
    char buffer[LEN_BUFFER] = {};
    getchar();

    while ((curr_c = getchar()) != '\n' && curr_c != EOF)
    {
        buffer[ind] = (char)curr_c;
        ind++;
    }

    if (is_quit(buffer))
    {
        printf("We appreciate your passion to knowledge!\n"
               "See you next time!\n");
        abort();
    }

    else
    {
        if ((sscanf(buffer, "%lf %lf %lf", ptr_a, ptr_b, ptr_c) == 3) && *ptr_a != NAN && *ptr_b != NAN && *ptr_c != NAN)
        {
            printf("scanned successfully\n");
            return SUCCESS;
        }

        else
        {
            printf("scanning failed\n"
                   "please try again\n");
            return FAIL;
        }
    }
}

void calculate_answer(Coeffs* ptr_coeff, Roots* ptr_root)
{
    assert(ptr_coeff != NULL);
    assert(ptr_root != NULL);

    double a = ptr_coeff->a;
    double b = ptr_coeff->b;
    double c = ptr_coeff->c;
    double d = 0;

    ptr_root->n_roots = return_n_root(ptr_coeff, &d);

    switch(ptr_root->n_roots)
    {
        case ONE_SOLUT:
        {
            ptr_root->x1 = -b/(2*a);
            ptr_root->x2 = -b/(2*a);
            break;
        }
        case ONE_SOLUTAO:
        {
            ptr_root->x1 = -c/b;
            ptr_root->x2 = -c/b;
            ptr_root->n_roots = ONE_SOLUT; // ?
            break;
        }
        case TWO_SOLUT:
        {
            ptr_root->x1 = (-b+sqrt(d))/(2*a);
            ptr_root->x2 = (-b-sqrt(d))/(2*a);
            break;
        }
        case ZERO_SOLUT:
        {
            ptr_root->x1 = NONE;
            ptr_root->x2 = NONE;
            break;
        }
        case INF:
        {
            ptr_root->x1 = INF;
            ptr_root->x2 = INF;
            break;
        }
        default:
        {
            printf("How?");
            break;
        }
    }
}


void print_answer(Roots* ptr_roots)
{
    assert(ptr_roots != NULL);

    double x1 = ptr_roots->x1;
    double x2 = ptr_roots->x2;

    switch(ptr_roots->n_roots)
    {
        case ZERO_SOLUT:
            printf("No solutions");
            break;

        case ONE_SOLUT:
        case ONE_SOLUTAO:
        {
            printf("x1 = %lg", x1);
            break;
        }

        case TWO_SOLUT:
            printf("x1 = %lg, x2 = %lg", x1, x2);
            break;

        case INF:
            printf("Undefined number of solution");
            break;

        default:
            printf("What've you just done?");
    }
}

int return_n_root(Coeffs* ptr_coeff, double* link_d) // coeff_ptr
{
    assert(ptr_coeff != NULL);
    assert(link_d != NULL);

    double a = ptr_coeff->a;
    double b = ptr_coeff->b;
    double c = ptr_coeff->c;

    int z_a = compare(a, 0),
        z_b = compare(b, 0),
        z_c = compare(c, 0);

    if (z_a && z_b && z_c)
    {
        printf("all coeffs are zero\n");
        return INF;
    }

    else if (z_a && z_b)
        return ZERO_SOLUT;

    else if (z_a && !z_b)
        return ONE_SOLUTAO;

    else
    {
        *link_d = b*b-4*a*c;

        if (compare(*link_d, 0))
            return ONE_SOLUT;

        if (*link_d < 0)
            return ZERO_SOLUT;

        if (*link_d > 0)
            return TWO_SOLUT;
    }

    return 0;
}


// Прата - препроцессор
// define

/*#define ANSWER(a b c | x1 x2 nr ;) x1r x2r nrr) \
    {{a, b, c}, {x1, x2, nr}, {x1r, x2r, nrr}},
  */
void start_tester(void)
{
    printf("hello\n");
    const int num_of_tests = 10;
   /* coeffs_data list_data[num_of_tests] =
        ANSWER(1 2 1 | 0 0 1    ;) -1 -1 1)
        ANSWER(0 4 2 | 0 0 -0.5 ;) -1 -1 1)
        ANSWER(1 2 1 | 0 0 999  ;) -1 -1 1)    */
    Data mass[num_of_tests] = // mass
        {{{1, 2,  1}, {0, 0, 0},  {   -1,    -1,   1}},
         {{0, 4,  2}, {0, 0, 0},  { -0.5,  -0.5,   1}},
         {{0, 0,  1}, {0, 0, 0},  {10000, 10000,   0}},
         {{1, 5, -6}, {0, 0, 0},  {   -6,     1,   2}},
         {{1, 5,  6}, {0, 0, 0},  {   -2,    -3,   2}},
         {{2, 4,  0}, {0, 0, 0},  {    0,    -2,   2}},
         {{1, 0, -9}, {0, 0, 0},  {   -3,     3,   2}},
         {{1, 0,  9}, {0, 0, 0},  {10000, 10000,   0}},
         {{0, 0,  0}, {0, 0, 0},  {  999,   999, 999}},
         {{1, 0, -4}, {0, 0, 0},  {   -2,     2,   2}}};

    for(int i = 0; i < num_of_tests; i++)
    {
        struct Data All_tests = mass[i];
        calculate_answer(&All_tests.coeffs, &All_tests.roots);
        printf("Test Number %d:\t", i+1);
        check_sample(All_tests);
    }
}
GREETING_STATUS start_greeting (void)
{
    printf("To initiate tester please enter 'yes'\n");

    char str[LEN_STR];
    scanf("%s", str);

    if (!strcmp(str, "yes") || !strcmp(str, "Yes") || !strcmp(str, "YES"))
        return YES;
    else
        return NO;
}

void check_sample(Data All_tests)
{
    int roots          = All_tests.roots.n_roots;
    int expected_roots = All_tests.roots_exp.n_roots;

    double x1          = All_tests.roots.x1,
           x2          = All_tests.roots.x2,
           expected_x1 = All_tests.roots_exp.x1,
           expected_x2 = All_tests.roots_exp.x2;

    if (roots == expected_roots && ((compare(x1, expected_x1) && compare(x2, expected_x2)) ||
        (compare(x2, expected_x1) && compare(x1, expected_x2))))
    {
        printf("works fine\n\n");
        printf("x1          = %lg|         x2 = %lg|roots          = %d\n",
                x1,                        x2,      roots);
        printf("-------------------------------------------------------------\n");
        printf("expected_x1 = %lg|expected_x2 = %lg|expected_roots = %d\n\n",
                expected_x1,      expected_x2,      expected_roots);
    }

    else
    {
        printf("works bad\n\n");
        printf("x1          = %lg|         x2 = %lg|roots          = %d\n",
                x1,                        x2,      roots);
        printf("-------------------------------------------------------------\n");
        printf("expected_x1 = %lg|expected_x2 = %lg|expected_roots = %d\n\n",
                expected_x1,      expected_x2,      expected_roots);
    }
}

COMPARE_STATUS compare(double var1, double var2)
{
    if (fabs(var1-var2) <= APROX)
        return EQUALE;
    else
        return NOT_EQUALE;
}

BOOL is_quit(const char* ptr_buffer)
{
    int index = 0;
    BOOL flag = FALSE;
    char ch = '\0';

    while ((ch = *(ptr_buffer+index)) != '\0')
    {

        if (*(ptr_buffer+index) == 'q')
        {
            flag = TRUE;
            break;
        }

        else
        {
            index++;
            continue;
        }
    }
    return flag;
}
