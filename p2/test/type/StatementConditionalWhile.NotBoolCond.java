// Type violation in line 6
// while condition expected type 'boolean' but found 'String[]'

class Test {
    public static void main(String[] args) {
        while (args) {}
    }
}
