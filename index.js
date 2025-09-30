const fs = require("fs");
const path = require("path");

const targetDir = process.argv[2] || ".";

function stripBom(str) {
  if (str.charCodeAt(0) === 0xfeff) {
    return str.slice(1);
  }
  return str;
}

function formatJsonFiles(dir) {
  const entries = fs.readdirSync(dir, { withFileTypes: true });

  for (const entry of entries) {
    const fullPath = path.join(dir, entry.name);

    if (entry.isDirectory()) {
      formatJsonFiles(fullPath);
    } else if (entry.isFile() && entry.name.endsWith(".json")) {
      try {
        let raw = fs.readFileSync(fullPath, "utf8");
        raw = stripBom(raw); // 🚑 strip BOM if present
        const parsed = JSON.parse(raw);
        const pretty = JSON.stringify(parsed, null, 2) + "\n";
        fs.writeFileSync(fullPath, pretty, "utf8");
        console.log(`Formatted: ${fullPath}`);
      } catch (err) {
        console.error(`❌ Error in ${fullPath}: ${err.message}`);
      }
    }
  }
}

formatJsonFiles(path.resolve(targetDir));
