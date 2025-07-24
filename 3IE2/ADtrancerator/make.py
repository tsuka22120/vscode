from pathlib import Path
import subprocess
import xml.etree.ElementTree as et

DRAWIO_PATH = '"C:\Program Files\draw.io\draw.io.exe"'
ROOT_DIR = Path(__file__).resolve().parent
INPUT_DIR = ROOT_DIR / "drawio"
OUTPUT_DIR = ROOT_DIR / "images"

def generate_image(input_path : Path):

    try:
        root = et.parse(str(input_path)).getroot()
    except et.ParseError:
        print(f"Error : Failed to parse XML file {input_path}")
        return

    # 1ページの場合pagesが存在しないのでデフォルトを1とする。
    pages = int(root.get("pages", 1))

    for page in range(pages):
        page_name = root[page].get("name")
        output_file_name = f"{input_path.stem}-{page_name}.svg"
        output_path = OUTPUT_DIR / output_file_name

        command = f'{DRAWIO_PATH} "{input_path}" -x -f svg -p {page} -o "{output_path}"'

        try:
            subprocess.run(command, check=True)
        except subprocess.CalledProcessError:
            print(f'Error : Failed to execute "{command}"')

if __name__ == "__main__":

    OUTPUT_DIR.mkdir(exist_ok=True)

    for file_path in INPUT_DIR.glob("*.drawio"):
        generate_image(file_path)
