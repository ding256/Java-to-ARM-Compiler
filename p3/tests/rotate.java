class Base {
    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int [ ] a = new int[3];
        a[0] = 1;
        a[1] = 0;
        a[2] = 0;
        int [ ][ ] rotation_matrix = new int [3][3];
        rotation_matrix[0][0] = 0;
        rotation_matrix[0][1] = -1;
        rotation_matrix[0][2] = 0;
        rotation_matrix[1][0] = 1;
        rotation_matrix[1][1] = 0;
        rotation_matrix[1][2] = 0;
        rotation_matrix[2][0] = 0;
        rotation_matrix[2][1] = 0;
        rotation_matrix[2][2] = 1;
        int [ ] b = new int[3];
        int i = 0;
        while(i < 3) {
            int j = 0, entry = 0;
            while(j < 3) {
                entry = entry + rotation_matrix[i][j] * a[j];
                j = j + 1;
            }
            b[i] = entry;
            i = i + 1;
        }
        System.out.println("Before rotation");
        i = 0;
        while(i < 3) {
            System.out.println(a[i]);
            i = i + 1;
        }
        System.out.println("After rotation");
        i = 0;
        while(i < 3) {
            System.out.println(b[i]);
            i = i + 1;
        }
    }
}