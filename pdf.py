from fpdf import FPDF

# Load the contents of the main.c file
<<<<<<< HEAD
<<<<<<< HEAD
with open("core/src/main.c", "r") as file:
=======
with open("/mnt/data/main.c", "r") as file:
>>>>>>> ab3183e (Added Prac1 Files)
=======
with open("core/src/main.c", "r") as file:
>>>>>>> 0f67727 (Update pdf.py)
    c_code = file.read()

# Initialize PDF
pdf = FPDF()
pdf.set_auto_page_break(auto=True, margin=15)
pdf.add_page()
pdf.set_font("Courier", size=10)

# Split the code into lines and add to PDF
for line in c_code.splitlines():
    pdf.cell(0, 5, txt=line, ln=True)

# Save the PDF
<<<<<<< HEAD
<<<<<<< HEAD
output_path = "main_c_code.pdf"
=======
output_path = "/mnt/data/main_c_code.pdf"
>>>>>>> ab3183e (Added Prac1 Files)
=======
output_path = "main_c_code.pdf"
>>>>>>> 0f67727 (Update pdf.py)
pdf.output(output_path)


