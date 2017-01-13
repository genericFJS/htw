#
# - this example shows how to use the -include option
# - TeXDoclet generated output (TeXDoclet.tex and TeXDoclet_preamble.tex) 
#   is included in another Latex document (MyDocument.tex) here
#

rm TeXDoclet.tex

# -imagespath ".." not needed here because path texdoclet_images is in subdir of MyDocument.tex

javadoc -docletpath TeXDoclet.jar \
	-doclet org.stfm.texdoclet.TeXDoclet \
	-noindex \
	-hyperref \
	-tree \
	-nopackagetoc \
	-output TeXDoclet.tex \
	-sourcepath ../../src \
	-subpackages filetransfer_udp \
 	-include \
 	-sectionlevel section

# option tree:
# -tree \
# no empty pagestyle
sed -i -e 's/\\thispagestyle{empty}/%\\thispagestyle{empty}/g' TeXDoclet.tex