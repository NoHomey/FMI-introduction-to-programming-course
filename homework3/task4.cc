#include <cstdio>
#include <new>

#define SIGN(n) (n < 0 ? -1 : 1)

typedef unsigned char Number;

class PositionOnChessBoard {
protected:
Number  column;
Number row;

public:
PositionOnChessBoard(const Number onBoardColumn = 0, const Number onBoardRow = 0);

Number getRow() const;

Number getColumn() const;

bool operator==(const PositionOnChessBoard& otherPositionOnChessBoard) const;
};

template<typename T>
class SpecializedVector {
protected:
Number count;

public:
SpecializedVector();

Number length() const;

virtual void push(const T element) = 0;

virtual T operator[](const Number index) const = 0;
};

class ChessFigureMovment : public SpecializedVector<PositionOnChessBoard> {
protected:
PositionOnChessBoard positions[8];

public:
ChessFigureMovment();

void push(const PositionOnChessBoard element) final;

PositionOnChessBoard operator[](const Number index) const final;
};

class ChessFigure;

class AllianceChessFigureVector : public SpecializedVector<const ChessFigure*> {
protected:
const ChessFigure** figures;

public:
AllianceChessFigureVector(const Number size);

~AllianceChessFigureVector();

bool isAllyAtPosition(const PositionOnChessBoard& positionOnBoard) const;

void push(const ChessFigure* element) final;

void removeTemporary(const PositionOnChessBoard& positionOnBoard);

void restore();

const ChessFigure* operator[](const Number index) const final;
};

class ChessFigure {
protected:
PositionOnChessBoard positionOnBoard;
const AllianceChessFigureVector* allies;

virtual void generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const = 0;

public:
ChessFigure(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance);

ChessFigure(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance);

virtual ~ChessFigure();

PositionOnChessBoard getPositionOnBoard() const;

virtual bool canCapture(const ChessFigure* figure) const;
};

class Rook : public ChessFigure {
protected:
void generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const final;

public:
Rook(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance);

Rook(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance);
};

class King : public ChessFigure {
protected:
bool static isValidPositionOnChessBoard(const PositionOnChessBoard& figurePositionOnBoard);

void static addToMovmentsIfPossible(const PositionOnChessBoard& movment, ChessFigureMovment& possibleMovments);

void generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const final;

public:
King(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance);

King(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance);

ChessFigureMovment allPossibleMovments() const;
};

class Bishop : public ChessFigure {
protected:
void generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const final;

public:
Bishop(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance);

Bishop(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance);
};

class Queen : public ChessFigure {
protected:
void generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const final;

public:
Queen(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance);

Queen(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance);

bool canCapture(const ChessFigure* figure) const final;
};

class Knight : public ChessFigure {
protected:
void generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const final;

public:
Knight(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance);

Knight(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance);
};

class KingVsAllOutcomer {
protected:
King opposingKing;
AllianceChessFigureVector all;

static King kingCreator(const PositionOnChessBoard& kingPosition); 

bool isTheGivenKingInCheckByAll(const King* king) const;

bool isKingInCheck() const;

bool kingHasNoMove();

public:
enum KingVsAllOutcome {check = 1, checkmate, stalemate, none};

enum ChessFigureType {queen, bishop, knight, rook, king};

static ChessFigureType charToChessFigureType(const char symbol);

KingVsAllOutcomer(const Number allianceCount);

~KingVsAllOutcomer();

void setKing(const char rawColumn, const Number rawRow);

void setFigure(const ChessFigureType figureType, const char rawColumn, const Number rawRow);

KingVsAllOutcome outcome();
};

template<typename T>
T input();

template<>
char input<char>();

template<>
Number input<Number>();

void printOutcome(const KingVsAllOutcomer::KingVsAllOutcome outcome);

int main() {
    const Number count = input<Number>();
    char figureType = '\0';
    char figureColumn = '\0';
    Number figureRow =  0;
    KingVsAllOutcomer outcomer = {count};
    for(Number index = 0; index < count; ++index) {
        figureType = input<char>();
        figureColumn = input<char>();
        figureRow = input<Number>();
        outcomer.setFigure(KingVsAllOutcomer::charToChessFigureType(figureType), figureColumn, figureRow);
    }
    figureColumn = input<char>();
    figureRow = input<Number>();
    outcomer.setKing(figureColumn, figureRow);
    printOutcome(outcomer.outcome());

    return 0;
}

PositionOnChessBoard::PositionOnChessBoard(const Number onBoardColumn, const Number onBoardRow)
: column{onBoardColumn}, row{onBoardRow} {}

Number PositionOnChessBoard::getRow() const {
    return row;
}

Number PositionOnChessBoard::getColumn() const {
    return column;
}

bool PositionOnChessBoard::operator==(const PositionOnChessBoard& otherPositionOnChessBoard) const {
    return (row == otherPositionOnChessBoard.row) && (column == otherPositionOnChessBoard.column);
}

template<typename T>
SpecializedVector<T>::SpecializedVector()
: count{0} {}

template<typename T>
Number SpecializedVector<T>::length() const {
    return count;
}

ChessFigureMovment::ChessFigureMovment()
: SpecializedVector{}, positions{} {}

void ChessFigureMovment::push(const PositionOnChessBoard element) {
    positions[count++] = element;
}

PositionOnChessBoard ChessFigureMovment::operator[](const Number index) const {
    return positions[index];
}

AllianceChessFigureVector::AllianceChessFigureVector(const Number size)
: SpecializedVector{}, figures{nullptr} {
    try {
        figures = new const ChessFigure*[size];
    } catch(const std::bad_alloc& error) {
        throw error;
    }
}

AllianceChessFigureVector::~AllianceChessFigureVector() {
    delete[] figures;
}

void AllianceChessFigureVector::push(const ChessFigure* element) {
    figures[count++] = element;
}

void AllianceChessFigureVector::removeTemporary(const PositionOnChessBoard& positionOnBoard) {
    Number index = 0;
    for(; index < count; ++index) {
        if(figures[index]->getPositionOnBoard() == positionOnBoard) {
            break;
        }
    }
    --count;
    const ChessFigure* tmp = figures[index];
    figures[index] = figures[count];
    figures[count] = tmp;
}

void AllianceChessFigureVector::restore() {
    count++;
}

const ChessFigure* AllianceChessFigureVector::operator[](const Number index) const {
    return figures[index];
}

bool AllianceChessFigureVector::isAllyAtPosition(const PositionOnChessBoard& positionOnBoard) const {
    for(Number index = 0; index < count; ++index) {
        if(figures[index]->getPositionOnBoard() == positionOnBoard) {
            return true;
        }
    }

    return false;
}

ChessFigure::ChessFigure(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance)
: positionOnBoard{static_cast<Number>(rawColumn - 'a'), static_cast<Number>(rawRow - 1)}, allies{alliance} {}

ChessFigure::ChessFigure(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance)
: positionOnBoard{figurePositionOnBoard}, allies{alliance} {}

ChessFigure::~ChessFigure() {}

PositionOnChessBoard ChessFigure::getPositionOnBoard() const {
    return positionOnBoard;
}

bool ChessFigure::canCapture(const ChessFigure* figure) const {
    ChessFigureMovment movment = {};
    generateAttackMovment(figure->getPositionOnBoard(), &movment);
    const Number length = movment.length();
    const bool attackMovment = length > 0;
    if(allies) {
        for(Number index = 0; index < length; ++index) {
            if(allies->isAllyAtPosition(movment[index])) {
                return false;
            }
        }
    }

    return attackMovment;
}

Rook::Rook(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance)
: ChessFigure{rawColumn, rawRow, alliance} {}

Rook::Rook(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance)
: ChessFigure{figurePositionOnBoard, alliance} {}

void Rook::generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const {
    const Number row = positionOnBoard.getRow();
    const Number figureRow = figurePositionOnBoard.getRow();
    const Number column = positionOnBoard.getColumn();
    const Number figureColumn = figurePositionOnBoard.getColumn();
    Number movmentStep = 1;
    if(row == figureRow) {
        if(column > figureColumn) {
            movmentStep = -1;
        }
        for(Number movmentColumn = column + movmentStep; movmentColumn != figureColumn; movmentColumn += movmentStep) {
            movment->push({movmentColumn, row});
        }
        movment->push(figurePositionOnBoard);
    } else if(column == figureColumn) {
        if(row > figureRow) {
            movmentStep = -1;
        }
        for(Number movmentRow = row + movmentStep; movmentRow != figureRow; movmentRow += movmentStep) {
            movment->push({column, movmentRow});
        }
        movment->push(figurePositionOnBoard);
    }
}

bool King::isValidPositionOnChessBoard(const PositionOnChessBoard& figurePositionOnBoard) {
    return (figurePositionOnBoard.getRow() <= 7) && (figurePositionOnBoard.getColumn() <= 7);
}

void King::addToMovmentsIfPossible(const PositionOnChessBoard& movment, ChessFigureMovment& possibleMovments) {
    if(isValidPositionOnChessBoard(movment)) {
        possibleMovments.push(movment);
    }
}

King::King(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance)
: ChessFigure{rawColumn, rawRow, alliance} {}

King::King(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance)
: ChessFigure{figurePositionOnBoard, alliance} {}

ChessFigureMovment King::allPossibleMovments() const {
    const Number column = positionOnBoard.getColumn();
    const Number row = positionOnBoard.getRow();
    const Number columnPlusOne = column + 1;
    const Number rowPlusOne = row + 1;
    const Number columnMinusOne = column - 1;
    const Number rowMinusOne = row - 1;
    ChessFigureMovment possibleMovments = {};
    addToMovmentsIfPossible({column, rowMinusOne}, possibleMovments);
    addToMovmentsIfPossible({columnPlusOne, rowMinusOne}, possibleMovments);
    addToMovmentsIfPossible({columnPlusOne, row}, possibleMovments);
    addToMovmentsIfPossible({columnPlusOne, rowPlusOne}, possibleMovments);
    addToMovmentsIfPossible({column, rowPlusOne}, possibleMovments);
    addToMovmentsIfPossible({columnMinusOne, rowPlusOne}, possibleMovments);
    addToMovmentsIfPossible({columnMinusOne, row}, possibleMovments);
    addToMovmentsIfPossible({columnMinusOne, rowMinusOne}, possibleMovments);

    return possibleMovments;
}

void King::generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const {
    const ChessFigureMovment possibleMovments = allPossibleMovments();
    const Number length = possibleMovments.length();
    for(Number index = 0; index < length; ++index) {
        if(possibleMovments[index] == figurePositionOnBoard) {
            movment->push(figurePositionOnBoard);
        }
    }
}

Bishop::Bishop(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance)
: ChessFigure{rawColumn, rawRow, alliance} {}

Bishop::Bishop(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance)
: ChessFigure{figurePositionOnBoard, alliance} {}

void Bishop::generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const {
    const Number row = positionOnBoard.getRow();
    const Number figureRow = figurePositionOnBoard.getRow();
    const Number column = positionOnBoard.getColumn();
    const Number figureColumn = figurePositionOnBoard.getColumn();
    const int rowDiff = figureRow - row;
    const int columnDiff = figureColumn - column;
    const int rowStep = SIGN(rowDiff);
    const int columnStep = SIGN(columnDiff);
    if((rowStep * rowDiff) == (columnStep * columnDiff)) {
        Number movmentRow = row + rowStep;
        Number movmentColumn = column + columnStep;
        for(; movmentRow != figureRow; movmentRow += rowStep, movmentColumn += columnStep) {
            movment->push({movmentColumn, movmentRow});
        }
        movment->push(figurePositionOnBoard);
    }
}

Queen::Queen(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance)
: ChessFigure{rawColumn, rawRow, alliance} {}

Queen::Queen(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance)
: ChessFigure{figurePositionOnBoard, alliance} {}

void Queen::generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const {}

bool Queen::canCapture(const ChessFigure* figure) const {
    const Bishop bishop = {positionOnBoard, allies};
    const Rook rook = {positionOnBoard, allies};

    return bishop.canCapture(figure) || rook.canCapture(figure);
}

Knight::Knight(const char rawColumn, const Number rawRow, const AllianceChessFigureVector* alliance)
: ChessFigure{rawColumn, rawRow, alliance} {}

Knight::Knight(const PositionOnChessBoard& figurePositionOnBoard, const AllianceChessFigureVector* alliance)
: ChessFigure{figurePositionOnBoard, alliance} {}

void Knight::generateAttackMovment(const PositionOnChessBoard& figurePositionOnBoard, ChessFigureMovment* movment) const {
    const Number row = positionOnBoard.getRow();
    const Number column = positionOnBoard.getColumn();
    bool threatening = false;
    const Number rowPlusOne = row + 1;
    const Number rowMinusOne = row - 1;
    const Number rowPlusTwo = row + 2;
    const Number rowMinusTwo = row - 2;
    const Number columnPlusOne = column + 1;
    const Number columnMinusOne = column - 1;
    const Number columnPlusTwo = column + 2;
    const Number columnMinusTwo = column - 2;
    if((PositionOnChessBoard{columnPlusOne, rowMinusTwo} == figurePositionOnBoard) || (PositionOnChessBoard{columnMinusOne, rowMinusTwo} == figurePositionOnBoard)) {
        movment->push({column, rowMinusOne});
        movment->push({column, rowMinusTwo});
        threatening = true;
    }
    if((PositionOnChessBoard{columnPlusOne, rowPlusTwo} == figurePositionOnBoard) || (PositionOnChessBoard{columnMinusOne, rowPlusTwo} == figurePositionOnBoard)) {
        movment->push({column, rowPlusOne});
        movment->push({column, rowPlusTwo});
        threatening = true;
    }
    if((PositionOnChessBoard{columnMinusTwo, rowPlusOne} == figurePositionOnBoard) || (PositionOnChessBoard{columnMinusTwo, rowMinusOne} == figurePositionOnBoard)) {
        movment->push({columnMinusOne, row});
        movment->push({columnMinusTwo, row});
        threatening = true;
    }
    if((PositionOnChessBoard{columnPlusTwo, rowPlusOne} == figurePositionOnBoard) || (PositionOnChessBoard{columnPlusTwo, rowMinusOne} == figurePositionOnBoard)) {
        movment->push({columnPlusOne, row});
        movment->push({columnPlusTwo, row});
        threatening = true;
    }
    if(threatening) {
        movment->push(figurePositionOnBoard);
    }
}

King KingVsAllOutcomer::kingCreator(const PositionOnChessBoard& kingPosition) {
    return {kingPosition, nullptr};
}

bool KingVsAllOutcomer::isTheGivenKingInCheckByAll(const King* king) const {
    const Number length = all.length();
    for(Number index = 0; index < length; ++index) {
        if(all[index]->canCapture(king)) {
            return true;
        }
    }

    return false;
}

bool KingVsAllOutcomer::isKingInCheck() const {
    return isTheGivenKingInCheckByAll(&opposingKing);
}

bool KingVsAllOutcomer::kingHasNoMove() {
    const ChessFigureMovment possibleMovmentsOfOpposingKing = opposingKing.allPossibleMovments();
    const Number length = possibleMovmentsOfOpposingKing.length();
    King king = kingCreator({});
    PositionOnChessBoard kingPosition = {};
    bool isPositionTaken = false;
    bool isKingInCheckByAll = false;
    for(Number index = 0; index < length; ++index) {
        kingPosition = possibleMovmentsOfOpposingKing[index];
        isPositionTaken = all.isAllyAtPosition(kingPosition);
        if(isPositionTaken) {
            all.removeTemporary(kingPosition);
        }
        king = kingCreator(possibleMovmentsOfOpposingKing[index]);
        isKingInCheckByAll = isTheGivenKingInCheckByAll(&king);
        if(isPositionTaken) {
            all.restore();
        }
        if(!isKingInCheckByAll) {
            return false;
        }
    }

    return true;
}

KingVsAllOutcomer::ChessFigureType KingVsAllOutcomer::charToChessFigureType(const char symbol) {
    switch(symbol) {
        case 'Q': return queen;
        case 'B': return bishop;
        case 'N': return knight;
        case 'R': return rook;
        default: return king;
    }
}

KingVsAllOutcomer::KingVsAllOutcomer(const Number allianceCount)
: opposingKing{kingCreator({})}, all{allianceCount} {}

KingVsAllOutcomer::~KingVsAllOutcomer() {
    const Number length = all.length();
    for(Number index = 0; index < length; ++index) {
        delete all[index];
    }
}

void KingVsAllOutcomer::setKing(const char rawColumn, const Number rawRow) {
    opposingKing = {rawColumn, rawRow, nullptr};
}

void KingVsAllOutcomer::setFigure(const ChessFigureType figureType, const char rawColumn, const Number rawRow) {
    switch(figureType) {
        case ChessFigureType::queen: {
            try {
                const Queen* queen = new Queen{rawColumn, rawRow, &all};
                all.push(queen);
            } catch(std::bad_alloc& error) {
                throw error;
            }
            break;
        }
        case ChessFigureType::bishop: {
            try {
                const Bishop* bishop = new Bishop{rawColumn, rawRow, &all};
                all.push(bishop);
            } catch(std::bad_alloc& error) {
                throw error;
            }
            break;
        }
        case ChessFigureType::knight: {
            try {
                const Knight* knight = new Knight{rawColumn, rawRow, &all};
                all.push(knight);
            } catch(std::bad_alloc& error) {
                throw error;
            }
            break;
        }
        case ChessFigureType::rook: {
            try {
                const Rook* rook = new Rook{rawColumn, rawRow, &all};
                all.push(rook);
            } catch(std::bad_alloc& error) {
                throw error;
            }
            break;
        }
        default: {
            try {
                const King* king = new King{rawColumn, rawRow, &all};
                all.push(king);
            } catch(std::bad_alloc& error) {
                throw error;
            }
        }
    }
}

KingVsAllOutcomer::KingVsAllOutcome KingVsAllOutcomer::outcome() {
    const bool noPossibleMove = kingHasNoMove();
    if(isKingInCheck()) {
        return noPossibleMove ? checkmate : check;
    }

    return noPossibleMove ? stalemate : none;
}

template<typename T>
T input();

template<>
char input<char>() {
    const char value = std::getchar();
    std::getchar();
    return value;
}

template<>
Number input<Number>() {
    return input<char>() - '0';
}

void printOutcome(const KingVsAllOutcomer::KingVsAllOutcome outcome) {
    switch(outcome) {
        case KingVsAllOutcomer::KingVsAllOutcome::check: {
            printf("Check");
            break;
        }
        case KingVsAllOutcomer::KingVsAllOutcome::checkmate: {
            printf("Checkmate");
            break;
        }
        case KingVsAllOutcomer::KingVsAllOutcome::stalemate: {
            printf("Stalemate");
            break;
        }
        default: printf("The show must go on");
    }
    printf("!\n");
}