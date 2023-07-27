class IsPrime {
    public static int sqrt(int number) {
        int result = 0;
        int square = 0;
        while (square <= number) {
            square = square + (2 * result + 1);
            result = result + 1;
        }
        return result - 1;
    }

    public static boolean isPrime(int number) {
        if (number <= 1) return false;
        else {
            int i = 2;
            while (i <= sqrt(number)) {
                int dividend = number;
                int divisor = i;
                int quotient = 0;
                while (dividend >= divisor) {
                    dividend = dividend - divisor;
                    quotient = quotient + 1;
                }
                if (dividend == 0) return false;
                else i = i + 1;
            }
            return true;
        }
    }

    public static void main(String[] args) {
        int number = Integer.parseInt(args[0]);
        if (isPrime(number)) System.out.println("true");
        else System.out.println("false");
    }

}
