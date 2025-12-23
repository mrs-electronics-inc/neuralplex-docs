# Docs Template

This project is hosted at https://replace-me.mrs-electronics.dev

## New Project Checklist

Follow these steps in every new docs repository.

- [ ] Use this template to create new repo - [link](https://github.com/new?template_name=docs-template&template_owner=mrs-electronics-inc)
- [ ] Configure new repo with correct settings - [docs](https://hub.mrs-electronics.dev/project-management/github-set-up/)
- [ ] Configure GitHub Pages
  - [ ] "GitHub Actions" as source
  - [ ] Add DNS config in AWS Route 53
  - [ ] Add custom domain in GitHub
- [ ] Create a pull request
  - [ ] Update the title in the README
  - [ ] Update the URL in the README
  - [ ] Update `astro.config.mjs` with appropriate configuration
  - [ ] Update `src/content/docs/index.mdx` with appropriate information
  - [ ] Update `public/site.webmanifest` with appropriate information
  - [ ] Update `package.json` with project name
  - [ ] Add any initial content
  - [ ] Remove the "New Project Checklist" from the README
- [ ] Merge the pull request
- [ ] Verify that deployment is successful
- [ ] Enable "Enforce HTTPS" in the GitHub pages settings (it does not seem you can do it until you have a deployment)

## Project Structure

Starlight looks for `.md` or `.mdx` files in the `src/content/docs/` directory. Each file is exposed as a route based on its file name.

Images can be added to `src/assets/` and embedded in Markdown with a relative link.

Static assets, like favicons, can be placed in the `public/` directory.

## Commands

All commands are run from the root of the project, from a terminal:

| Command         | Action                                      |
| :-------------- | :------------------------------------------ |
| `npm install`   | Installs dependencies                       |
| `npm run dev`   | Starts local dev server at `localhost:4321` |
| `npm run build` | Build your production site to `dist/`       |
