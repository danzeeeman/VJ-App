cd ../../../addons

if [ -z $1 ]; then
    PREFIX="git clone https://github.com/"
else
    PREFIX="git clone git@github.com:"
fi


${PREFIX}P-A-N/ofxAlembic.git
${PREFIX}frauzufall/ofxGuiExtended.git
${PREFIX}leadedge/ofxNDI 