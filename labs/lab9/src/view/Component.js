/**
 * @implements {IComponent}
 */
class Component {
    /**
     * @param {{
     *   tagName: (?string),
     *   blockName: (?string),
     *   elementNS: (?string),
     * }} args
     */
    constructor({tagName = "div", blockName = "", elementNS}) {
        /**
         * @type {!Element}
         * @private
         */
        this._element = elementNS
            ? document.createElementNS(elementNS, tagName)
            : document.createElement(tagName);

        /**
         * @type {string}
         * @private
         */
        this._blockName = blockName
        blockName && this.addClassName(blockName);

        /**
         * @type {!Array<!function(Event)>}
         * @private
         */
        this._onClickHandlers = [];
    }

    /**
     * @override
     */
    displayObject() {
        return this._element;
    }

    /**
     * @override
     */
    addChild(child, index) {
        const childElement = this._getElement(child);

        if (index != null)
        {
            const referenceElement = this._element.childNodes[index];
            if (referenceElement)
            {
                this._element.insertBefore(childElement, referenceElement);
                return;
            }
        }
        this._element.appendChild(childElement);
    }

    /**
     * @override
     */
    removeChild(child) {
        const childElement = this._getElement(child);

        if (this.hasChild(childElement))
        {
            this._element.removeChild(childElement);
        }
    }

    /**
     * @override
     */
    hasChild(child) {
        return child.parentNode == this._element;
    }

    /**
     * @override
     */
    addClassName(value) {
        this._element.classList.add(value);
    }

    /**
     * @override
     */
    setAttribute(name, value) {
        this._element.setAttribute(name, value);
    }

    /** @override */
    setX(value) {
        this._element.style.left = `${value}px`;
    }

    /** @override */
    setY(value) {
        this._element.style.top = `${value}px`;
    }

    /** @override */
    setWidth(value) {
        this._element.style.width = `${value}px`;
    }

    /** @override */
    setHeight(value) {
        this._element.style.height = `${value}px`;
    }

    /**
     * @param {!Element|!IComponent} item
     * @return {!Element}
     * @private
     */
    _getElement(item) {
        return (item instanceof Element) ? item : item.displayObject();
    }
}

export {Component}
