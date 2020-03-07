---
layout: post
title: "Your First Blog Post"
date: 2020-03-07 11:10:00
author: Dylan Colli
---

# Welcome!

This is the first blog post in a series where I'm going to be walking through how I built Ingreedyents. This blog post will cover how I got up and running with building the Jekyll site on my local machine and how I made this very same blog post. 

I'm setting up the Jekyll site to build locally since it just isn't feasible to rely on GitHub to build my site every time I want to check the layout/prototype the website.

## Choosing A Jekyll Theme

I'm starting off by looking at the Jekyll theme that I think is most appropriate. The [Jekyll Doc Theme](https://aksakalli.github.io/jekyll-doc-theme/docs/home/) includes a place for documentation as well as a place for a blog, so I think this is a good choice. I've also used [Just The Docs](https://pmarsceill.github.io/just-the-docs/docs/) when building documentation for my position in the Campbell Muscle Lab at the University of Kentucky and that was very easy and enjoyable. The reason I'm opting for the former option is due to the blogging component. I want to share the knowledge I develop while I'm building this fun project!

## Setting Up the Documentation

Now it's time to actually start setting things up. I'm following the directions on the [github README](https://github.com/aksakalli/jekyll-doc-theme) pretty much to a tee. I already have Ruby and Jekyll installed, so I'm going to skip over how to install those (it's very easy and instructions are included in the README if you need them).

I've created a `docs` directory as well as a `_config.yml` file, a Gemfile, and a very simple `index.md` file in that directory. The `_config.yml` file has the following contents:

```yaml
remote_theme: aksakalli/jekyll-doc-theme@gh-pages 
```

The `Gemfile` looks like:

```gemfile
gem "github-pages", group: :jekyll_plugins
```

And `index.md` looks like this:

```md
---
# This is the front matter, this provides metadata on the page.
title: Home Page
permalink: /
---

This is the home page.
```

Now to build the site for the very first time, you open up a terminal, navigate to the `docs` directory, and execute:

```
$ bundle exec jekyll serve
```

Which builds the site and allows you to access the site at `localhost:4000`.

If everything went right, you should see the home page! Congratulations! Now that we have that set up, we're going to take a look at how to set up the blog and make our first post.

## Setting up the Blog

Now that we have the base website built, we can start working on getting our very first blog post up.

To begin this, I've created a directory, `docs/_posts` and created a file with today's date, March 7, 2020 as the title of the post. This file is called, `2020-03-07-first-post.md` and contains:

```md
---
layout: post
title: "Your First Blog Post"
date: 2020-03-07 11:10:00
author: Dylan Colli
---

--INSERT POST HERE--
```

Where --INSERT POST HERE-- is simply the contents of this post (how's that for recursion?).

And that's it! That wasn't so bad! Simply commit what you've written, push to GitHub, and the site will be built wherever your GitHub pages redirects to.

To summarize, I've commited the following files:
  + `docs/_posts/2020-03-07-first-post.md`
  + `docs/_config.yml`
  + `docs/Gemfile`
  + `docs/index.md`
  + Changes to `.gitignore` to ignore all of the generated files for the Jekyll site. Namely `docs/_site` and `docs/Gemfile.lock`.