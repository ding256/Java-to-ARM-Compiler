class PerfectSquareAndCube {
    public static int findPerfectSquareAndCubes(int n, int num, int count) {
        if (count < n) {
            if (isSquare(num, 1) && isCube(num, 1)) {
                count = count + 1;
            } else {
                count = count;
            }
            return findPerfectSquareAndCubes(n, num + 1, count);
        } else {
            return num-1;
        }
    }

    public static boolean isSquare(int num, int i) {
        if (i * i > num) return false;
        else if (i * i == num) return true;
        else return isSquare(num, i + 1);
    }

    public static boolean isCube(int num, int j) {
        if (j * j * j > num) return false;
        else if (j * j * j == num) return true;
        else return isCube(num, j + 1);
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(findPerfectSquareAndCubes(n, 1, 0));
    }
}


