DR. SANTOS' STUDENT REGISTRY
============================

WHAT THIS PROGRAM DOES
-----------------------
A command-line C program that lets Dr. Santos manage up to 10 student
records during a session. Each student has:
  - ID (int)
  - Name (char array / string)
  - Major (char array / string)
  - GPA (float)
  - Credits taken (int)

She can:
  1. Add a new student
  2. Display all students in a formatted table
  3. Search for one student by ID and see their full record
  4. Find every student with GPA >= a threshold she enters
  5. Find every student in a given major, with a count

FILES
-----
  student_registry.c   -- the complete source code
  sample_input.txt      -- example input used to test the program
  sample_output.txt     -- the resulting output from that test run

HOW TO COMPILE AND RUN
-----------------------
  gcc -Wall -o registry student_registry.c
  ./registry

MY APPROACH
------------
- I bundled each student's five pieces of data into one `struct Student`.
  This keeps a student's information together as ONE unit, instead of
  juggling five separate parallel arrays (one for IDs, one for names,
  etc.) which gets confusing and error-prone.
- I then declared `Student students[MAX_STUDENTS]` as a global array,
  which is the "array of structs" pattern -- it satisfies the "Arrays"
  requirement while keeping related data together, exactly like a row
  in a spreadsheet.
- `studentCount` tracks how many of the 10 slots are actually filled,
  and every function checks it with a simple `for` loop bounded by
  `studentCount` (not MAX_STUDENTS), so we never read uninitialized
  slots.
- Each menu action lives in its own function (addStudent, 
  displayAllStudents, searchById, searchByGpaThreshold, searchByMajor)
  to keep main() clean and each responsibility separate, per the
  "Functions" requirement.
- addStudent() checks studentCount against MAX_STUDENTS first (the
  "check limits" conditional) and also rejects duplicate IDs.
- scanf() is used for numbers (int, float) and fgets() is used for
  strings (name, major) so that names with spaces like "Alice Johnson"
  are read correctly. clearInputBuffer() cleans up the leftover
  newline after scanf so it doesn't interfere with the next fgets().
- Searches use simple if-conditionals inside for-loops:
    - Search by ID: exact match, stop at first hit (there should only
      be one, since duplicate IDs are blocked at creation).
    - Search by GPA: keep every student whose gpa >= threshold, and
      count matches.
    - Search by major: exact string match (strcmp), display each and
      report a running count of "matches" at the end.

TESTING
-------
sample_input.txt feeds the program 5 students (Alice, Bob, Charlie,
Diana, Ethan), then:
  - displays all of them
  - looks up ID 1005 (Ethan Santos) and gets his full record
  - queries GPA >= 3.5 (returns Alice, Charlie, Diana)
  - queries major "Computer Science" (returns Alice, Charlie, Ethan,
    count = 3)
  - exits

You can reproduce this test yourself with:
  ./registry < sample_input.txt > sample_output.txt

POSSIBLE FUTURE IMPROVEMENTS (not required for this exercise)
---------------------------------------------------------------
- Saving/loading student data to a file so it persists between runs.
- Editing or deleting an existing student's record.
- Sorting the display (by GPA, name, or ID).
