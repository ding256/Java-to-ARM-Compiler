class SumOfNaturalNumbers {
    public static int sumOfN(int n) {
        if (n <= 0) return 0;
        else return n + sumOfN(n - 1);
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(sumOfN(n));
    }
}
