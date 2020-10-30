"""projecteuler.net problem 22. Names scores.

Using https://projecteuler.net/project/resources/p022_names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
"""
import csv


def get_name_score(name):
    """Get scrore of name.

    :param name: string name to score.
    :return: score of name
    :rtype: int
    >>> get_name_score("")
    0
    >>> get_name_score("COLIN")
    53
    """
    total_score = 0
    for c in name:
        letter_score = ord(c) - ord("A") + 1
        assert letter_score > 0 and letter_score <= 26, f"letter out of range: {c}"
        total_score += letter_score
    return total_score


def get_names_scores(filename):
    """Get score from all names in a file.

    :param filename: name of file of names
    :return: score of all names
    """
    # File somewhat resembles a csv file.
    with open("names.txt", "r") as f:
        r = csv.reader(f)
        names = [row for row in r][0]
    score = 0
    names.sort()
    for x in range(len(names)):
        score += get_name_score(names[x]) * (x + 1)
    return score


if __name__ == "__main__":
    import doctest

    doctest.testmod()

    print(get_names_scores("names.txt"))
