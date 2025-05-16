/* This plugin is based on the plugin listed in this page - https://dan.salvagni.io/b/astro-plugin-open-external-links-in-new-tab/ */
import type { RehypePlugin } from "@astrojs/markdown-remark";
import { visit } from "unist-util-visit";
import type { Element } from "hast";

export const targetBlank: RehypePlugin = () => {
  return (tree) => {
    visit(tree, "element", (e: Element) => {
      if (
        e.tagName === "a" &&
        e.properties?.href &&
        e.properties.href.toString().startsWith("http")
      ) {
        // Apply blank target on external links.
        e.properties!["target"] = "_blank";
      }
    });
  };
};
