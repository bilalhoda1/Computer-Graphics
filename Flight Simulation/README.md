# Project I: Flight Simulator
# CS 440 Computer Graphics, Fall 2019

## Purpose

This project brings together many of the topics we have covered in Module I by implementing:

- viewing
- shading
- interaction
- geometry

## The Problem Set

The problems are defined in `main.tex` which is to be compiled using a LaTeX compiler.

## Time Requirement.

Based on feedback from the last set of students that attempted this assignment, the number of hours that your team will require to complete this homework are as follows.

- (min, max) : (10, 60)
- (mean, median, st.dev.) : (32.61, 35, 15.03)

## Grading

The marks for this assignment are shown in `rubric.csv`.

## Submission

There are 2 parts to the submission.

### 1. Problem Set

Your code will be run by the instructor _as is_ so make sure to include online links to any non-submitted files that are used by your code, i.e. those from the `Common` folder.

_Deadline_: 18h on Wednesday, 6 November.

### 2. Feedback Form

You have to provide feedback on your team and on the assignment by filling the form at [LMS -> Tests & Quizzes](https://lms.habib.edu.pk/x/WwHsDI). This is due at the same time as the problem solutions.

_Deadline_: 18h on Wednesday, 6 November.

## Review Notes

Add your notes at the end of this README by including a new section with the heading, _Submission Notes_. These notes would include information on

- the controls
- any choices you have made in the code with regard to efficiency 
- any bonus functionality you have implemented

## Tips

- This project involves a lot of work so start early.
- There is no late submission. Submit whatever you have by the deadline.
- Failure to turn in any of the above submissions will result in withholding of marks for the homework.
- Clearly indicate all required information in your _Submission Notes_.
- viel Spaß!


## Discussion

There is a lot to handle and there are bound to be confusions and queries. Please share them using the following avenues.

- discuss with your partner
- post in the [class forum](https://habibedu.facebook.com/groups/1062098287331314/)
- discuss with your peers
- talk to course staff.

----------

## Submission Notes
Following keypresses control the flight simulation:
- W: Top
- A: Left
- S: Bottom
- D: Right
- F: Far
- N: Near
- +: Accelerate
- -: Deccelerate
- I: Pitch up
- K: Pitch down
- L: Roll right
- J: Roll left
- Left-arrow key: Yaw left
- Right-arrow key: Yaw right
- T: Initially, the wireframe display is shown, pressing T once will display a flat shaded enviornment, pressing T twice would result in smooth shading.\
- P: Pause/Unpause the audio.

Bonus functionality implemented is listed below:
- Height map is not completely random, it accounts for the neighboring points and yields a smoother terrain
- Added sound effects, by default sound is mute and will be triggered upon pressing its button

