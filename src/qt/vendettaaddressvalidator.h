// Copyright (c) 2011-2014 The Vendetta Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef VENDETTA_QT_VENDETTAADDRESSVALIDATOR_H
#define VENDETTA_QT_VENDETTAADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class VendettaAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit VendettaAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Vendetta address widget validator, checks for a valid vendetta address.
 */
class VendettaAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit VendettaAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // VENDETTA_QT_VENDETTAADDRESSVALIDATOR_H
