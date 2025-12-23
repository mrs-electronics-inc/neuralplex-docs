// @ts-check
import { defineConfig, passthroughImageService } from 'astro/config';
import starlight from '@astrojs/starlight';
import { targetBlank } from "./src/plugins/targetBlank";

// https://astro.build/config
export default defineConfig({
	site: "https://neuralplex.dev",
	base: "/",
	outDir: "public",
	publicDir: "static",
	markdown: {
		rehypePlugins: [[targetBlank, {}]],
	},
	integrations: [
		starlight({
			title: 'NeuralPlex Docs',
			logo: {
				src: './src/assets/MRS_Logo.png',
			},
			social: [{ icon: 'gitlab', label: 'GitLab', href: 'https://gitlab.com/mrs-neuralplex' }],
			customCss: [
				'./src/styles/custom.css',
			],
			sidebar: [
				{
					label: 'General Information & Safety',
					autogenerate: { directory: "general" },
				},
				{
					label: 'Getting Started',
					autogenerate: { directory: 'getting-started' },
				},
				{
					label: 'Hardware',
					autogenerate: { directory: 'hardware' },
				},
				{
					label: 'Qt Programming',
					autogenerate: { directory: 'qt' },
				},
				{
					label: 'Operating System',
					autogenerate: { directory: 'operating-system' },
				},
				{
					label: 'Yocto',
					autogenerate: { directory: 'yocto' },
				},
				{
					label: 'Other',
					autogenerate: { directory: 'other' },
				},
			],
			favicon: "/favicon.ico",
		}),
	],
	image: {
		// This avoids Sharp, which seems to not always work. Haven't noticed any sort of decrease in performance.
		// It was also removed from the package.json for one less dependency.
		service: passthroughImageService(), 
	},
});
