import sys
import re

"""Names exercise

Define the extract_names() function below and change main() to call it.

For writing regex, it's nice to include a copy of the target text for inspiration.

Here's what the html looks like in the baby.html files:
...
<h3 align="center">Popularity in 1990</h3>
....
<tr align="right"><td>1</td><td>Michael</td><td>Jessica</td>
<tr align="right"><td>2</td><td>Christopher</td><td>Ashley</td>
<tr align="right"><td>3</td><td>Matthew</td><td>Brittany</td>
...

Suggested milestones for incremental development:
 -Extract the year and print it
 -Extract the names and rank numbers and just print them
 -Get the names data into a dict and print it
 -Build the [year, 'name rank', ... ] list and print it
 -Fix main() to use the extract_names list
"""


def extract_names(filename):
    """
    Given a file name for baby.html, returns a list starting with the year string
    followed by the name-rank strings in alphabetical order.
    ['2006', 'Aaliyah 91', Aaron 57', 'Abagail 895', ' ...]
    """
    # +++your code here+++
    f = open(filename, "r")
    content = f.read()
    f.close()
    year_pattern = re.compile(r"<h3.+</h3>")
    h3 = re.search(year_pattern, content).group()
    if not h3:
        print("not find h3")
        return
    year = re.search(r"\d{4}", h3).group()
    print(year)
    name_pattern = re.compile(r"<td>(\d+)</td><td>(\w+)</td><td>(\w+)</td>")
    name_list = name_pattern.findall(content)
    names = [year]
    for s in name_list:
        names.append(s[1] + " " + s[0])
        names.append(s[2] + " " + s[0])
    names.sort()
    f = open(f"{filename}Result.txt", "w")
    for name in names:
        f.write(name + "\n")
    f.close()
    print(f"finish! it has been written to {filename}Result.txt file")
    return


def main():
    # This command-line parsing code is provided.
    # Make a list of command line arguments, omitting the [0] element
    # which is the script itself.
    args = sys.argv[1:]

    if not args:
        print('usage: [--summaryfile] file [file ...]')
        sys.exit(1)

    # Notice the summary flag and remove it from args if it is present.
    summary = False
    if args[0] == '--summaryfile':
        summary = True
        del args[0]

    # +++your code here+++
    # For each filename, get the names, then either print the text output
    # or write it to a summary file
    for filename in args:
        extract_names(filename)


if __name__ == '__main__':
    main()
