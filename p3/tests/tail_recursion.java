class Factorial {
    public static int factorial(int x, int acc) {
        if(x == 1 || x == 0) {
            return acc;
        } else {
            return factorial(x - 1, acc * x);
        }
    }

    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int a = factorial(6, 1);
        System.out.println(a);
    }
}
