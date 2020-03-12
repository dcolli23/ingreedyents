"""Quick script for writing the boilerplate for a new blog post."""
import os
import datetime

ROOT = os.path.dirname(__file__)
POSTS_DIR = os.path.join(ROOT, "_posts")

HEADER_TEMPLATE = """---
layout: post
title: 
date: {0} {1}
author: Dylan Colli
---

"""

EDITOR = "code"

def main():
  """Writes the boilerplate for a new blog post into a new file"""
  # Get the date and time in a formatted string.
  today = datetime.datetime.today()
  date_formatted = today.strftime("%Y-%m-%d")
  time_formatted = today.strftime("%H:%M:%S")

  # Form the file name and path.
  file_name = date_formatted+"-post.md"
  file_path = os.path.join(POSTS_DIR, file_name)

  # Make the new header.
  header = HEADER_TEMPLATE.format(date_formatted, time_formatted)

  with open(file_path, 'w') as f:
    f.write(header)
  
  os.system(EDITOR+" "+file_path)

if __name__ == "__main__":
  main()