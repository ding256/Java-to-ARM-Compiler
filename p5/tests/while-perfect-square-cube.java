class PerfectSquareAndCube {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int count = 0;
        int num = 1;
        int result = 0;

        while (count < n) {
            int i = 1;
            boolean isSquare = false;
            while (i * i <= num && !isSquare) {
                if (i * i == num) {
                    isSquare = true;
                } else {
                    isSquare = false;
                }
                i = i + 1;
            }

            if (isSquare) {
                int j = 1;
                boolean isCube = false;
                while (j * j * j <= num && !isCube) {
                    if (j * j * j == num) {
                        isCube = true;
                    } else {
                        isCube = false;
                    }
                    j = j + 1;
                }

                if (isCube) {
                    result = num;
                    count = count + 1;
                } else {
                    count = count;
                }
            } else {
                count = count;
            }

            num = num + 1;
        }
        System.out.println(result);
    }
}
